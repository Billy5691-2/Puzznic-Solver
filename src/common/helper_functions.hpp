#ifndef B1D235EC_A2A8_4785_AEEC_044AE6A82F53
#define B1D235EC_A2A8_4785_AEEC_044AE6A82F53
#include <vector>
#include <iostream>

namespace HelperFunctions {
  template <typename t>
  void PrintVector(const std::vector<t>& vec, int newLineInterval)
  {
    for (int i = 0; i < vec.size; i++)
    {
      std::cout << vec[i];
      if (i % newLineInterval == 0)
      {
        std::cout << "\n";
      }
    }
  }

  template <typename t>
  void VectorAppendToStart(const std::vector<t>& dataVec, std::vector<t>* targetVec)
  {
    targetVec->reserve(targetVec->size() + dataVec.size());
    targetVec->insert(targetVec->begin(), dataVec.begin(), dataVec.end());
  }

  template <typename t>
  void VectorAppendToEnd(const std::vector<t>& dataVec, std::vector<t>* targetVec)
  {
    targetVec->reserve(targetVec->size() + dataVec.size());
    targetVec->insert(targetVec->end(), dataVec.begin(), dataVec.end());
  }
}  // namespace HelperFunctions


#endif /* B1D235EC_A2A8_4785_AEEC_044AE6A82F53 */
