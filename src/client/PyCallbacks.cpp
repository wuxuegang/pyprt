/**
 * Esri CityEngine SDK Geometry Encoder for Python
 *
 * Copyright 2014-2019 Esri R&D Zurich and VRBN
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "PyCallbacks.h"

#include <string>
#include <vector>
#include <map>


void PyCallbacks::addGeometry(
    const size_t initialShapeIndex,
    const double* vertexCoords,
    const size_t vertexCoordsCount,
    const uint32_t* facesIndices,
    const uint32_t* faceCounts,
    const size_t faceCountsCount) {

    if (vertexCoords != nullptr)
        mModels[initialShapeIndex].mVertices.insert(mModels[initialShapeIndex].mVertices.end(), vertexCoords, vertexCoords + vertexCoordsCount);


    if (facesIndices != nullptr) { // THERE IS A MISTAKE HERE!!!!
        for (uint32_t ind = 0; ind < faceCountsCount; ind++) {
            std::vector<uint32_t> v(facesIndices, facesIndices + faceCounts[ind]);
            mModels[initialShapeIndex].mFaces.insert(mModels[initialShapeIndex].mFaces.end(), v);
        }
    }
}

void PyCallbacks::addReports(
    const size_t initialShapeIndex,
    const wchar_t** stringReportKeys,
    const wchar_t** stringReportValues,
    size_t stringReportCount,
    const wchar_t** floatReportKeys,
    const double* floatReportValues,
    size_t floatReportCount,
    const wchar_t** boolReportKeys,
    const bool* boolReportValues,
    size_t boolReportCount) {

    BoolMap boolReport;
    FloatMap floatReport;
    StringMap stringReport;

    for (size_t i = 0; i < boolReportCount; i++) {
        boolReport[boolReportKeys[i]] = boolReportValues[i];
    }
    mModels[initialShapeIndex].mCGABoolReport = boolReport;

    for (size_t i = 0; i < floatReportCount; i++) {
        floatReport[floatReportKeys[i]] = floatReportValues[i];
    }
    mModels[initialShapeIndex].mCGAFloatReport = floatReport;

    for (size_t i = 0; i < stringReportCount; i++) {
        stringReport[stringReportKeys[i]] = stringReportValues[i];
    }
    mModels[initialShapeIndex].mCGAStringReport = stringReport;
}