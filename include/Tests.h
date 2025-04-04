#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

#include "Service.h"

void writeResultsToCSV(const std::string& filename, const std::vector<std::pair<double, double>>& times) {
    std::string resultsFolder = "results";
    std::string filePath = resultsFolder + "/" + filename;
    std::ofstream file(filePath);
    file << "Parameter; Time * e^6\n";
    for (const auto& time : times)
        file << time.first << ";" << time.second * 1000000 << "\n";
    file.close();
    std::cout << "Results saved in file '" << filename << "'\n";
}

void test1(int testNumber, const std::string& algorithmType) {
    std::string fileName = "test" + std::to_string(testNumber) + "_" + algorithmType + ".csv";
    std::ofstream results(fileName);
    std::vector<std::pair<double, double>> times;
    for (int i = 100; i <= 10000; i += 100) {
        std::vector<Segment> dataSample = Service::randomSegments(i, 1.0);
        auto start_time = std::chrono::high_resolution_clock::now();
        if (algorithmType == "naive")
            Service::intersectNaive(dataSample, i);
        else if (algorithmType == "effective_AVLTree")
            Service::intersectEffectiveAVLTree(dataSample, i);
        else if (algorithmType == "effective_Tree23")
            Service::intersectEffectiveTree23(dataSample, i);
        auto end_time = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double>(end_time - start_time).count();
        times.push_back({ i, duration });
    }
    writeResultsToCSV(fileName, times);
}

void test2(int testNumber, const std::string& algorithmType) {
    std::string fileName = "test" + std::to_string(testNumber) + "_" + algorithmType + ".csv";
    std::ofstream results(fileName);
    std::vector<std::pair<double, double>> times;
    int n = 10003;
    for (int k = 1; k <= 10000; k += 100) {
        std::vector<Segment> dataSample = Service::randomSegments(n, k);
        auto start_time = std::chrono::high_resolution_clock::now();
        if (algorithmType == "naive")
            Service::intersectNaive(dataSample, k);
        else if (algorithmType == "effective_AVLTree")
            Service::intersectEffectiveAVLTree(dataSample, k);
        else if (algorithmType == "effective_Tree23")
            Service::intersectEffectiveTree23(dataSample, k);
        auto end_time = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double>(end_time - start_time).count();
        times.push_back({ k, duration });
    }
    writeResultsToCSV(fileName, times);
}

void test3(int testNumber, const std::string& algorithmType) {
    std::string fileName = "test" + std::to_string(testNumber) + "_" + algorithmType + ".csv";
    std::ofstream results(fileName);
    std::vector<std::pair<double, double>> times;
    for (double r = 0.001; r <= 0.01; r += 0.0001) {
        std::vector<Segment> dataSample = Service::randomSegments(10000, r);
        auto start_time = std::chrono::high_resolution_clock::now();
        if (algorithmType == "naive")
            Service::intersectNaive(dataSample, 10000);
        else if (algorithmType == "effective_AVLTree")
            Service::intersectEffectiveAVLTree(dataSample, 10000);
        else if (algorithmType == "effective_Tree23")
            Service::intersectEffectiveTree23(dataSample, 10000);
        auto end_time = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double>(end_time - start_time).count();
        times.push_back({ r, duration });
    }
    writeResultsToCSV(fileName, times);
}

void test4(int testNumber, const std::string& algorithmType) {
    std::string fileName = "test" + std::to_string(testNumber) + "_" + algorithmType + ".csv";
    std::ofstream results(fileName);
    std::vector<std::pair<double, double>> times;
    for (double r = 0.0001; r <= 0.01; r += 0.0001) {
        std::vector<Segment> dataSample = Service::randomSegments(10000, r);
        auto start_time = std::chrono::high_resolution_clock::now();
        if (algorithmType == "naive")
            Service::intersectNaive(dataSample, 10000);
        else if (algorithmType == "effective_AVLTree")
            Service::intersectEffectiveAVLTree(dataSample, 10000);
        else if (algorithmType == "effective_Tree23")
            Service::intersectEffectiveTree23(dataSample, 10000);
        auto end_time = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double>(end_time - start_time).count();
        times.push_back({ r, duration });
    }
    writeResultsToCSV(fileName, times);
}