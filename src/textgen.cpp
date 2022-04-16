// Copyright 2022 Open Cascade team
// Author: Semen Smirnov

// My includes
#include "textgen.h"

TextGenerator::TextGenerator(const std::string& theFilePath) noexcept {
  std::ifstream anIfStream;
  anIfStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    anIfStream.open(theFilePath);

    std::string aCurrentWord;
    prefix aNext;

    for (int aWordNumber = 0; aWordNumber < myPrefixLength; ++aWordNumber) {
      anIfStream >> aCurrentWord;
      aNext.push_back(aCurrentWord);
    }

    myStart = aNext;
    while (anIfStream >> aCurrentWord) {
      myStateTab[aNext].push_back(aCurrentWord);

      aNext.pop_front();
      aNext.push_back(aCurrentWord);
    }

    anIfStream.close();
  } catch (std::ifstream::failure /*theEx*/) {
    std::cerr << "Exception opening/reading/closing file";
  }
}

TextGenerator::TextGenerator(const std::string & theFilePath,
                             const int thePrefixLength,
                             const int theGenWordsNumber) noexcept {
  myPrefixLength = thePrefixLength;
  myGeneratedWordsNumber = theGenWordsNumber;

  std::ifstream anIfStream;
  anIfStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    anIfStream.open(theFilePath);

    std::string aCurrentWord;
    prefix aNext;

    for (int aWordNumber = 0; aWordNumber < myPrefixLength; ++aWordNumber) {
      anIfStream >> aCurrentWord;
      aNext.push_back(aCurrentWord);
    }

    myStart = aNext;
    while (!anIfStream.eof()) {
      anIfStream >> aCurrentWord;
      myStateTab[aNext].push_back(aCurrentWord);

      aNext.pop_front();
      aNext.push_back(aCurrentWord);
    }

    anIfStream.close();
  }
  catch (std::ifstream::failure theEx) {
    std::cerr << "Exception opening/reading/closing file";
  }
}

void TextGenerator::setPrefixLength(const int thePrefixLength) noexcept {
  myPrefixLength = thePrefixLength;
}

int TextGenerator::getPrefixLength() const noexcept {
  return myPrefixLength;
}

void TextGenerator::setGeneratedWordsNumber(const int theGenWordsNumber)
                                            noexcept {
  myGeneratedWordsNumber = theGenWordsNumber;
}

int TextGenerator::getGeneratedWordsNumber() const noexcept {
  return myGeneratedWordsNumber;
}

std::vector<TextGenerator::prefix> TextGenerator::getPrefix() const noexcept {
  std::vector<TextGenerator::prefix> aCurrentVectorPrefix;

  for (auto&& aPair : myStateTab) {
    aCurrentVectorPrefix.push_back(aPair.first);
  }

  return aCurrentVectorPrefix;
}

std::map<TextGenerator::prefix, std::vector<std::string>>
TextGenerator::getStateTab() const noexcept {
  return myStateTab;
}

std::vector<std::string> TextGenerator::getSuffix(const prefix& thePrefix)
                                                  const noexcept {
  return myStateTab.find(thePrefix)->second;
}

void TextGenerator::generate(const std::string & theFilePath) {
  std::ofstream anOfStream;
  anOfStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);

  try {
    anOfStream.open(theFilePath);

    srand(time(NULL));

    for (int aWordNumber = 0; aWordNumber < myPrefixLength; ++aWordNumber) {
      anOfStream << myStart[aWordNumber] << " ";
    }

    std::map<prefix, std::vector<std::string>>::iterator anMapIterator;
    prefix aNext(myStart);
    std::string aSuffix;

    for (int aWordNumber = 0; aWordNumber < myGeneratedWordsNumber;
      ++aWordNumber) {
      anMapIterator = myStateTab.find(aNext);
      if (anMapIterator != myStateTab.end()) {
        int size = anMapIterator->second.size();
        aSuffix = anMapIterator->second[rand() % size];
        anOfStream << aSuffix << " ";
        aNext.pop_front();
        aNext.push_back(aSuffix);
      } else {
        break;
      }
    }

    anOfStream.close();
  } catch (std::ofstream::failure /*theEx*/) {
    std::cerr << "Exception opening/reading/closing file";
  }
}
