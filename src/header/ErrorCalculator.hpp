#ifndef ERROR_CALCULATOR_H
#define ERROR_CALCULATOR_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <numeric>
#include "ImagePixel.hpp"
class ErrorCalculator {
public:
    enum ErrorMethod {
        VARIANCE = 1,
        MEAN_ABSOLUTE_DEVIATION = 2,
        MAX_PIXEL_DIFFERENCE = 3,
        ENTROPY = 4,
        SSIM = 5
    };
    static double calculateError(ErrorMethod method, const std::vector<std::vector<Pixel>>& block, double& rValue, double& gValue, double& bValue);
private:
    static double calculateVariance(const std::vector<std::vector<Pixel>>& block, double& rMean, double& gMean, double& bMean);
    static double calculateMAD(const std::vector<std::vector<Pixel>>& block, double& rMean, double& gMean, double& bMean);
    static double calculateMaxDiff(const std::vector<std::vector<Pixel>>& block, double& rMean, double& gMean, double& bMean);
    static double calculateEntropy(const std::vector<std::vector<Pixel>>& block, double& rMean, double& gMean, double& bMean);
    static double calculateSSIM(const std::vector<std::vector<Pixel>>& block, double& rMean, double& gMean, double& bMean);
    static void calculateMeans(const std::vector<std::vector<Pixel>>& block, double& rMean, double& gMean, double& bMean);
    static void calculateHistograms(const std::vector<std::vector<Pixel>>& block, std::map<uint8_t, int>& rHist, std::map<uint8_t, int>& gHist,std::map<uint8_t, int>& bHist);
};


#endif