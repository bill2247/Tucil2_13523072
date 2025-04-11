#include "../header/ErrorCalculator.hpp"

double ErrorCalculator::calculateError(ErrorMethod method, 
                           const std::vector<std::vector<Pixel>>& block,
                           double& rValue, double& gValue, double& bValue) {
    switch (method) {
        case VARIANCE: return calculateVariance(block, rValue, gValue, bValue);
        case MEAN_ABSOLUTE_DEVIATION: return calculateMAD(block, rValue, gValue, bValue);
        case MAX_PIXEL_DIFFERENCE: return calculateMaxDiff(block, rValue, gValue, bValue);
        case ENTROPY: return calculateEntropy(block, rValue, gValue, bValue);
        default: throw std::invalid_argument("Invalid error method");
    }
}

double ErrorCalculator::calculateVariance(const std::vector<std::vector<Pixel>>& block,
                              double& rMean, double& gMean, double& bMean) {
    calculateMeans(block, rMean, gMean, bMean);
    
    double maxVariance = 16256.25;
    double rVar = 0, gVar = 0, bVar = 0;
    int count = 0;
    
    for (const auto& row : block) {
        for (const Pixel& p : row) {
            rVar += (p.r - rMean) * (p.r - rMean);
            gVar += (p.g - gMean) * (p.g - gMean);
            bVar += (p.b - bMean) * (p.b - bMean);
            count++;
        }
    }
    
    rVar /= count;
    gVar /= count;
    bVar /= count;
    
    return (rVar + gVar + bVar) / (3.0 * maxVariance);
}

double ErrorCalculator::calculateMAD(const std::vector<std::vector<Pixel>>& block,
                         double& rMean, double& gMean, double& bMean) {
    calculateMeans(block, rMean, gMean, bMean);
    
    double maxMAD = 127.5;
    double rMad = 0, gMad = 0, bMad = 0;
    int count = 0;
    
    for (const auto& row : block) {
        for (const Pixel& p : row) {
            rMad += std::abs(p.r - rMean);
            gMad += std::abs(p.g - gMean);
            bMad += std::abs(p.b - bMean);
            count++;
        }
    }
    
    rMad /= count;
    gMad /= count;
    bMad /= count;
    
    return (rMad + gMad + bMad) / (3.0 * maxMAD);
}

double ErrorCalculator::calculateMaxDiff(const std::vector<std::vector<Pixel>>& block,
                             double& rMean, double& gMean, double& bMean) {
    const double diffMax = 255.0;
    if (block.empty() || block[0].empty()) return 0.0;
    
    uint8_t rMin = block[0][0].r, rMax = block[0][0].r;
    uint8_t gMin = block[0][0].g, gMax = block[0][0].g;
    uint8_t bMin = block[0][0].b, bMax = block[0][0].b;
    
    for (const auto& row : block) {
        for (const Pixel& p : row) {
            rMin = std::min(rMin, p.r);
            rMax = std::max(rMax, p.r);
            gMin = std::min(gMin, p.g);
            gMax = std::max(gMax, p.g);
            bMin = std::min(bMin, p.b);
            bMax = std::max(bMax, p.b);
        }
    }
    
    rMean = (rMax + rMin) / 2.0;
    gMean = (gMax + gMin) / 2.0;
    bMean = (bMax + bMin) / 2.0;
    
    double rDiff = rMax - rMin;
    double gDiff = gMax - gMin;
    double bDiff = bMax - bMin;
    
    return (rDiff + gDiff + bDiff) / (3.0 * diffMax);
}

double ErrorCalculator::calculateEntropy(const std::vector<std::vector<Pixel>>& block, double& rMean, double& gMean, double& bMean) {
    calculateMeans(block, rMean, gMean, bMean);
    
    std::map<uint8_t, int> rHist, gHist, bHist;
    calculateHistograms(block, rHist, gHist, bHist);
    
    double maxEntropy = 8.0;
    int totalPixels = block.size() * block[0].size();
    double rEntropy = 0, gEntropy = 0, bEntropy = 0;
    
    for (const auto& pair : rHist) {
        double prob = pair.second / static_cast<double>(totalPixels);
        rEntropy -= prob * log2(prob);
    }
    
    for (const auto& pair : gHist) {
        double prob = pair.second / static_cast<double>(totalPixels);
        gEntropy -= prob * log2(prob);
    }
    
    for (const auto& pair : bHist) {
        double prob = pair.second / static_cast<double>(totalPixels);
        bEntropy -= prob * log2(prob);
    }
    
    return (rEntropy + gEntropy + bEntropy) / (3.0 * maxEntropy);
}

void ErrorCalculator::calculateMeans(const std::vector<std::vector<Pixel>>& block, double& rMean, double& gMean, double& bMean) {
    rMean = gMean = bMean = 0.0;
    int count = 0;
    
    for (const auto& row : block) {
        for (const Pixel& p : row) {
            rMean += p.r;
            gMean += p.g;
            bMean += p.b;
            count++;
        }
    }
    
    if (count > 0) {
        rMean /= count;
        gMean /= count;
        bMean /= count;
    }
}

void ErrorCalculator::calculateHistograms(const std::vector<std::vector<Pixel>>& block, std::map<uint8_t, int>& rHist, std::map<uint8_t, int>& gHist,std::map<uint8_t, int>& bHist) {
    rHist.clear();
    gHist.clear();
    bHist.clear();
    
    for (const auto& row : block) {
        for (const Pixel& p : row) {
            rHist[p.r]++;
            gHist[p.g]++;
            bHist[p.b]++;
        }
    }
}

