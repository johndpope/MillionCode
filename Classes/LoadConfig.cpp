//
//  LoadConfig.cpp
//  MillionCode
//
//  Created by 木村巧 on 2015/04/20.
//
//

#include "LoadConfig.h"
#include "DataKey.h"
#include "Generic.h"

using namespace cocos2d;
using namespace std;

bool LoadConfig::Load(const string fileName)
{
    auto fileUtils = FileUtils::getInstance();
    string filePath = fileUtils->fullPathForFilename(fileName.c_str());
    long nSize = 1024;
    unsigned char* pBuffer = fileUtils->getFileData(filePath.c_str(), "r", &nSize);
    
    string *data = new string((char*)pBuffer);
    CCLOG("%s",data->c_str());
    delete[] pBuffer;
    
    int StartTag;
    int EndTag;
    int MonsterCount = 0;
    string MonsterName;
    
    //dataの中身がなくなるまでループ
    while(!data->empty())
    {
        //指定されたタグを探す
        StartTag = data->find("<", 0);
        EndTag = data->find(">", 0);
        
        if(EndTag != string::npos && EndTag != 0)
        {
            //config.txtに登録されているモンスターの数
            MonsterCount++;
            
            //「StartTag」と「EndTag」の間にある文字列を取得
            MonsterName = data->substr(StartTag + 1, EndTag - 1);
            
            //MonsterCount(int型)をString型に変換
            string MonsterNum = Generic::intToStrnig(MonsterCount);
            
            //saveKeyの名前を生成
            string saveKey = SaveDataKey[n_DataKeyNum::eMonsterKey] + MonsterNum;
            
            //データを保存
            CCUserDefault::getInstance()->setStringForKey(saveKey.c_str(), MonsterName);
            CCUserDefault::getInstance()->flush();
            
            //「StartTag」から「EndTag」を削除
            //改行も１文字として判定されるので">"+改行分で「+2」
            data->erase(StartTag, EndTag + 2);
            
            //===================== testLoad + log ============================================
            string test = CCUserDefault::getInstance()->getStringForKey(saveKey.c_str());
            CCLOG("StartTag:%d\nEndTag:%d", StartTag, EndTag);
            CCLOG("testKey:%s \ntestNum:%d", MonsterNum.c_str(), MonsterCount);
            CCLOG("SaveKey:%s", saveKey.c_str());
            CCLOG("load:%s", test.c_str());
            CCLOG("monstername:%s", MonsterName.c_str());
            CCLOG("%s",data->c_str());
            //==================================================================================
            
            //初期化
            EndTag = 0;
            StartTag = 0;
            
            //whileループの最初に戻る
            continue;
        }
        //"#"を発見したらブレイク
        if(data->find("#", 0) != string::npos ) break;
    }
    CCLOG("end while");
    CCUserDefault::getInstance()->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterTotal].c_str(), MonsterCount);
    CCUserDefault::getInstance()->flush();
    
    delete data;
    return true;
}