#pragma once


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>



std::vector<std::string> readGLSLfile (std::string filename){


    std::ifstream file(filename);
    std::vector<std::string> content;

    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            content.push_back (line);
        }
    } else {
        std::cerr << "Can't open the file named " << filename << std::endl;
    }

    file.close();
    return content;
}

void writeGLSLfile (std::string filename, std::vector<std::string> newContent){
    std::ofstream outputFile(filename, std::ios::out | std::ios::trunc);

    if (outputFile.is_open()){
        for (auto s : newContent){
            outputFile << s << std::endl;
        }
    }
    else {
        std::cerr << "Can't open the file named " << filename << std::endl;
    }
    outputFile.close();
}

// uniform vec3 lightPos[4];
// uniform vec3 lightColor[4];
// for(int i = 0; i < 4; ++i) 
std::string _changeNumber (std::string line, int old, int num){
    std::string newLine = "";
    for (auto c : line){
        if (c == std::to_string(old)[0]){
            newLine = newLine + std::to_string(num);
        }
        else {
            newLine = newLine + c;
        }
    }
    return newLine;
}

void changeNumberLight (std::string filename, int oldNumber, int newNumber) {
    std::vector<std::string> oldContent = readGLSLfile(filename);

    std::vector<std::string> newContent;
    std::string newLine = "\n";
    std::string line;

    std::string uniformPos = "uniformvec3lightPos["+std::to_string(oldNumber)+"];";
    std::string uniformCol = "uniformvec3lightColor["+std::to_string(oldNumber)+"];";
    std::string forLine = "for(inti=0;i<"+std::to_string(oldNumber)+";++i)";

    for (auto line : oldContent){
        std::string line_wo_space = line;
        line_wo_space.erase(
            std::remove_if(line_wo_space.begin(), 
                            line_wo_space.end(), 
                            [](char c){ return std::isspace(static_cast<unsigned char>(c));}), 
            line_wo_space.end());
        
        if (line_wo_space.compare(uniformPos) == 0 
            || line_wo_space.compare(uniformCol) == 0
            || line_wo_space.compare(forLine) == 0){
            std::string newLine = _changeNumber(line, oldNumber, newNumber);
            newContent.push_back(newLine);
        }
        else {
            newContent.push_back(line);
        }
    }
    writeGLSLfile(filename, newContent);
}