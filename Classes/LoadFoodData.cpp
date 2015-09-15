#include "LoadFoodData.h"

using namespace cocos2d;
using namespace std;

const string NameKey = "FoodDataKey";
string LoadFoodData::saveNameKey = "";

void LoadFoodData::loadName(string fname, string folderPath){
    /*
    int nStartTag;
    int nEndTag;
    int Count = 0;
    
    
    string namePath = folderPath + fname + ".txt";
    
    FileUtils* fileUtils = FileUtils::getInstance();
    std::string filePath = fileUtils->fullPathForFilename(namePath.c_str());
    long nSize = 1024;
    unsigned char* pBuffer = fileUtils->getFileData(filePath.c_str(), "r", &nSize);
    
    string* data = new string((char*)pBuffer);
    CCLOG("%s", pBuffer);
    delete [] pBuffer;
    
    while(!data->empty()){
        
        nStartTag = data->find("<", 0);
        nEndTag = data->find(">", 0);
        
        if(nEndTag != string::npos && nEndTag != 0){
            
            string name = data->substr(nStartTag + 1, nEndTag - 1);
            
            
            
            data->erase(nStartTag, nEndTag + 2);
            
            CCLOG("name:%s", name.c_str());
            
            
            CCLOG("StartTag:%d\nEndTag:%d", nStartTag, nEndTag);
            CCLOG("%dname::%s", Count, name.c_str());
            
            
            nStartTag = 0;
            nEndTag = 0;
            
            
            stringstream cvCount;
            cvCount << Count;
            const string nameCount = cvCount.str();
            
            CCLOG("%s", nameCount.c_str());
            
            
            saveNameKey = SaveDataKey[n_DataKeyNum::eFoodDataKey] + nameCount;
            
            CCLOG("%s", saveNameKey.c_str());
            
            
            CCUserDefault::getInstance()->setStringForKey(saveNameKey.c_str(), name);
            CCUserDefault::getInstance()->flush();
            
            
            Count = atoi(nameCount.c_str());
            Count++;
            
            CCLOG("Count:%d", Count);
            CCLOG("saveFile:%s",saveNameKey.c_str());
            
            
            continue;
        }
        
        if(data->find("#", 0) != string::npos)
            break;
        
    }
    CCLOG("End While");
    CCLOG("%d", Count);
    
    
    CCUserDefault::getInstance()->setIntegerForKey("FoodTotal", Count);
    CCUserDefault::getInstance()->flush();
    
    //FoodStatus(fname, folderPath);
     *
     */
}


FST LoadFoodData::foodStatus(string fname, string folderPath){
	/*
    long fSize = 1024;         
    
    int nCount = CCUserDefault::getInstance()->getIntegerForKey("FoodTotal");
    
    int fsCount = 0;
    int Count = 0;
    FST fst;
    
    CCLOG("nCount::%d",nCount);
    
    CCLOG("%s", saveNameKey.c_str());
    
    while(fsCount < nCount){
        
        std::stringstream cvCount;
        cvCount << fsCount;
        std::string nameCount = cvCount.str();
        
        
        saveNameKey = SaveDataKey[n_DataKeyNum::eFoodDataKey] + nameCount;
        
        
        string nameData = CCUserDefault::getInstance()->getStringForKey(saveNameKey.c_str());
        
        CCLOG("%s", nameData.c_str());
        
        
        //string fsName = CCUserDefault::sharedUserDefault()->getStringForKey(nameData.c_str());
        string pPath = folderPath + nameData + ".txt";
        
        CCLOG("%s", nameData.c_str());
        CCLOG("%s", pPath.c_str());
        
        unsigned char* foodData = CCFileUtils::getInstance()->getFileData(pPath.c_str(), "r", &fSize);
        string* fsData = new string((const char*)foodData, fSize);
        
        
        fst.hp = 0;
        fst.atk = 0;
        fst.def = 0;
        fst.dex = 0;
        
        fst.hp = foodAnalysis("HP", *fsData);
        fst.atk = foodAnalysis("ATK", *fsData);
        fst.def = foodAnalysis("DEF", *fsData);
        fst.dex = foodAnalysis("DEX", *fsData);
        fst.eva = foodAnalysis("陰陽=", *fsData);
        
        
        CCLOG("upStatusStart");
        CCLOG("upStatus:%d", fst.hp);
        CCLOG("upStatus:%d", fst.atk);
        CCLOG("upStatus:%d", fst.def);
        CCLOG("upStatus:%d", fst.dex);
        CCLOG("upStatus:%d", fst.eva);
        fsCount++;
        CCLOG("++fsCount:%d", fsCount);
        
        
        continue;
    }
    
    return fst;
    */
}


int LoadFoodData::foodAnalysis(string keyword, string data){
    /*
    CCLOG("%s",keyword.c_str());
    int status;
    int key = data.find(keyword, 0);
    int end;
    int stTag;
    
    if(keyword == "陰陽="){
        stTag = data.find("陰陽=", 0);
        end = data.find(";", key);
        
        
        string word = data.substr(key + keyword.size(), end - 1);
        
       
        status = atoi(word.c_str());
    }
    
    else if(key != string::npos)
    {
        stTag = data.find("Up=", key);
        end = data.find(";", stTag);
        
        CCLOG("%d", stTag);
        CCLOG("%d", end);
        
        
        string word = data.substr(stTag+3, end - 1);
        CCLOG("Tag::%d:%d", stTag+3, end -1);
        
        
        status = atoi(word.c_str());
    }
    else if(key == string::npos){
        status = 0;
    }
    
    CCLOG("int status = %d", status);
    //CCLog("data::%s", data.c_str());
    return status;

    */
}
