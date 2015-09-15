#include "MonsterData.h"

using namespace std;
using namespace cocos2d;

ST MonsterData::loadMonsterData(string monster, string folderpath) {
    string pPath = folderpath + monster + ".txt";
    
    string filePath = FileUtils::getInstance()->fullPathForFilename(pPath.c_str());
    CCLOG("%s", filePath.c_str());
    long nSize = 1024;
    unsigned char* pBuffer = FileUtils::getInstance()->getFileData(filePath.c_str(), "r", &nSize);
    
    string *data = new string((char*)pBuffer);
    CCLOG("%s",data->c_str());
    delete[] pBuffer;
    
    ST st;
    
    st.name       = "NoName";
    st.race       = monster;
    st.lv         = 1;
    st.exp        = 0;
    st.stuff      = 0;
    st.effort.hp  = 0;
    st.effort.atk = 0;
    st.effort.dfe = 0;
    st.effort.dex = 0;
    st.st.hp      = monsterAnalysisInt("HP=", *data);
    st.st.atk     = monsterAnalysisInt("ATK=", *data);
    st.st.dfe     = monsterAnalysisInt("DFE=", *data);
    st.st.dex     = monsterAnalysisInt("DEX=", *data);
    st.gf.hp      = monsterAnalysisInt("GF-HP=", *data);
    st.gf.atk     = monsterAnalysisInt("GF-ATK=", *data);
    st.gf.dfe     = monsterAnalysisInt("GF-DFE=", *data);
    st.gf.dex     = monsterAnalysisInt("GF-DEX=", *data);
    st.evoLv      = monsterAnalysisInt("EvoLv=", *data);
    st.criteria   = monsterAnalysisInt("Criteria=", *data);
    st.evoNega    = monsterAnalysisString("EvoNega=", *data);
    st.evoPosi    = monsterAnalysisString("EvoPosi=", *data);
    st.evo        = monsterAnalysisString("Evo=", *data);
    
    CCLOG("%d",st.st.hp);
    CCLOG("%d",st.st.atk);
    CCLOG("%d",st.st.dfe);
    CCLOG("%d",st.st.dex);
    CCLOG("%d",st.gf.hp);
    CCLOG("%d",st.gf.atk);
    CCLOG("%d",st.gf.dfe);
    CCLOG("%d",st.gf.dex);
    CCLOG("%d",st.evoLv);
    CCLOG("%d",st.criteria);
    CCLOG("%s",st.evoPosi.c_str());
    CCLOG("%s",st.evoNega.c_str());
    CCLOG("%s",st.evo.c_str());
    
    
    return st;
}

ST MonsterData::monsterSaveDataAnalysis(string key) {
    string data = UserDefault::getInstance()->getStringForKey(key.c_str(), "Null");
    ST st;
    st.name       = monsterAnalysisString("Name=", data);
    st.race       = monsterAnalysisString("Race=", data);
    st.lv         = monsterAnalysisInt("Lv=", data);
    st.exp        = monsterAnalysisInt("Exp=", data);
    st.stuff      = monsterAnalysisInt("Stuff=", data);
    st.st.hp      = monsterAnalysisInt("HP=", data);
    st.st.atk     = monsterAnalysisInt("ATK=", data);
    st.st.dfe     = monsterAnalysisInt("DFE=", data);
    st.st.dex     = monsterAnalysisInt("DEX=", data);
    st.gf.hp      = monsterAnalysisInt("GF-HP=", data);
    st.gf.atk     = monsterAnalysisInt("GF-ATK=", data);
    st.gf.dfe     = monsterAnalysisInt("GF-DFE=", data);
    st.gf.dex     = monsterAnalysisInt("GF-DEX=", data);
    st.effort.hp  = monsterAnalysisInt("EF-HP=", data);
    st.effort.atk = monsterAnalysisInt("EF-ATK=", data);
    st.effort.dfe = monsterAnalysisInt("EF-DFE=", data);
    st.effort.dex = monsterAnalysisInt("EF-DEX=", data);
    st.evoLv      = monsterAnalysisInt("EvoLv=", data);
    st.criteria   = monsterAnalysisInt("Criteria=", data);
    st.evoNega    = monsterAnalysisString("EvoNega=", data);
    st.evoPosi    = monsterAnalysisString("EvoPosi=", data);
    st.evo        = monsterAnalysisString("Evo=", data);
    
    CCLOG("%d",st.st.hp);
    CCLOG("%d",st.st.atk);
    CCLOG("%d",st.st.dfe);
    CCLOG("%d",st.st.dex);
    CCLOG("%d",st.gf.hp);
    CCLOG("%d",st.gf.atk);
    CCLOG("%d",st.gf.dfe);
    CCLOG("%d",st.gf.dex);
    CCLOG("%d",st.evoLv);
    CCLOG("%d",st.criteria);
    CCLOG("%s",st.evoPosi.c_str());
    CCLOG("%s",st.evoNega.c_str());
    CCLOG("%s",st.evo.c_str());
    return st;
}

int MonsterData::monsterAnalysisInt(string keyword, string data) {
    int status = 0;
    int key = data.find(keyword, 0);
    if(key != string::npos)
    {
        int end = data.find(";", key);
        
       
        string word = data.substr(key + keyword.size(), end - 1);
        
        
        status = atoi(word.c_str());
    }
    CCLOG("int status = %d", status);
    return status;
}

string MonsterData::monsterAnalysisString(string keyword, string data) {
    string status;
    int key = data.find(keyword, 0);
    if ( key != string::npos ) {
        int end = data.find(";", key);
        
        string word = data.substr(key + keyword.length(), end - 1);
        word = word.erase(word.find(";", 0));
        status = word.c_str();
    }
    return status;
}

void MonsterData::saveMonsterData(ST st, string key) {
    string data = "";
    data += "Name=" + st.name + ";\n"
    + "Race=" + st.race + ";\n"
    + "Lv=" + Generic::intToStrnig(st.lv) + ";\n"
    + "Exp=" + Generic::intToStrnig(st.exp) + ";\n"
    + "Stuff=" + Generic::intToStrnig(st.stuff) + ";\n"
    + "HP=" + Generic::intToStrnig(st.st.hp) + ";\n"
    + "ATK=" + Generic::intToStrnig(st.st.atk) + ";\n"
    + "DFE=" + Generic::intToStrnig(st.st.dfe) + ";\n"
    + "DEX=" + Generic::intToStrnig(st.st.dex) + ";\n"
    + "GF-HP=" + Generic::intToStrnig(st.gf.hp) + ";\n"
    + "GF-ATK=" + Generic::intToStrnig(st.gf.atk) + ";\n"
    + "GF-DFE=" + Generic::intToStrnig(st.gf.dfe) + ";\n"
    + "GF-DEX=" + Generic::intToStrnig(st.gf.dex) + ";\n"
    + "EF-HP=" + Generic::intToStrnig(st.effort.hp) + ";\n"
    + "EF-ATK=" + Generic::intToStrnig(st.effort.atk) + ";\n"
    + "EF-DFE=" + Generic::intToStrnig(st.effort.dfe) + ";\n"
    + "EF-DEX=" + Generic::intToStrnig(st.effort.dex) + ";\n"
    + "EvoLv=" + Generic::intToStrnig(st.evoLv) + ";\n"
    + "Criteria=" + Generic::intToStrnig(st.criteria) + ";\n"
    + "EvoNega=" + st.evoNega + ";\n"
    + "EvoPosi=" + st.evoPosi + ";\n"
    + "Evo=" + st.evo + ";";
    
    UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    UserDefault::getInstance()->flush();
}
