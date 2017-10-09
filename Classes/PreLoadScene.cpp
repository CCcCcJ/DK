#include "PreLoadScene.h"
#include "LanguageString.h"
#include "ConstUtil.h"
#include "ui/CocosGUI.h"
#include "AudioControlScene.h"
#include"sqlite3.h"
#include "GameScene2.h"
int PreLoad::type=0;
char ** PreLoad::result=NULL;
int LEVEL;
namespace androidsql
{
	bool isFileExist(const char* pFileName)
	{
		if (!pFileName)return false;
		std::string filePath = FileUtils::getInstance()->getWritablePath();
		filePath.append(pFileName);
		log("%s-----", filePath.c_str());
		FILE *pFp = fopen(filePath.c_str(), "r");
		if (pFp)
		{
			fclose(pFp);
			return true;
		}
		return false;
	}
	void  copyData(const char * pFileName)
	{

		std::string strPath = FileUtils::getInstance()->fullPathForFilename(pFileName);
		ssize_t len = 0;
		unsigned char* data = NULL;
		data = FileUtils::getInstance()->getFileData(strPath.c_str(), "r", &len);
		std::string destPath = FileUtils::getInstance()->getWritablePath();

		destPath.append(pFileName);
		FILE *pFp = fopen(destPath.c_str(), "w+");
		fwrite(data, sizeof(char), len, pFp);
		fclose(pFp);
		delete[]data;
		data = NULL;

		//BOOL bresult = CopyFile(destPath.c_str(),strPath.c_str(),false);

	}
}
 Scene* PreLoad::createScene(int x,int selectLevel)
 {

	 type = x;
	 LEVEL = selectLevel;
	 auto scene = Scene::create();
	 auto layer = PreLoad::create();
	 scene->addChild(layer);
	 return scene;
 }

 bool PreLoad::init()
 {
	 if (!Layer::init())
	 {
		 return false;
	 }
	 finshflag = false;
	 Size visibleSize = Director::getInstance()->getVisibleSize();
	 auto load_text = cocos2d::ui::Text::create(LanguageString::getInstance()->getLanguageString(LOADING)->getCString(), "Arial", 16);
	 load_text->setPosition(Vec2(visibleSize.width*0.25, visibleSize.height*0.7));
	 this->addChild(load_text);
	 this->schedule(schedule_selector(PreLoad::progressupdate), 3.0f);

	 loadMusic();
	 sqlite3 *db = NULL;//声明sqlite关键结构指针
	 char *zErrMsg = 0;
	 int rc;
	 //打开指定的数据库文件,如果不存在,将创建一个同名的数据库文件,需要传入db这个指针的指针，因为sqlite3_open函数要为这,个指针分配内存，好要让db指针指向这个内存区
	 auto path = FileUtils::getInstance()->getWritablePath() + "word.db";
	 rc = sqlite3_open(path.c_str(), &db);
	 if (rc != SQLITE_OK)
	 {
		 Label *blee = Label::createWithSystemFont("openfail", "Verdana-Bold", 20);
		 blee->setPosition(visibleSize.width / 2 + 50, visibleSize.height / +50);
		 blee->setScale(1.0f);
		 blee->setColor(Color3B::RED);
		 this->addChild(blee);

		 //或者直接是rc
		 fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		 sqlite3_close(db);
		 exit(1);//打开失败，退出
	 }
	 else
		 log("You have opened a sqlite3 database named query.db successfully!\nCongratulation! Have fun!\n");
	 //创建一个表
	 char *sql = "CREATE TABLE SensorData(ID INTEGER PRIMARY KEY,SensorID INTEGER,SiteNum INTEGER,name VARCHAR(12),Sensorparamter REAL);";
	 sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	 //如果前面已经定义了_DEBUG_ ，则输出所创建的表存在的信息
#ifdef _DEBUG_ 
#define _DEBUG_
	 log("%s\n", zErrMsg);
#endif
	 //插入数据
	 //	sql = "INSERT INTO\"SensorData\"VALUES(NULL,1,1,'悄悄的',18.9);";//向要表中输入内容
	 //sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	 //sql = "INSERT INTO\"SensorData\"VALUES(NULL,1,1,'小小的',16.4);";
	 //sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	 int row = 0, column = 0;//用于记录下面结果集中的行数和列数
							 //char **
	 ;//二维数组用于存放结果
	  //查询语句，其在C语言中对应的函数接口是sqlite3_get_table(db,sql,&result,&row,&column,&zErrMsg)			
	 sql = "select * from vocabulary";
	 sqlite3_get_table(db, sql, &result, &row, &column, &zErrMsg);//result：以数组的形式存放所要查询的数据，首先是表名，然后才是数据
	 int i = 0;
	 log("row:%d column:%d\n", row, column);
	 log("\nThe result of querying is:\n"); 


	 Label *bleed = Label::createWithSystemFont("mirbase_succeed", "Verdana-Bold", 30);
	 bleed->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	 bleed->setScale(1.0f);
	 bleed->setColor(Color3B::RED);
	 this->addChild(bleed);
	 //for (i = 2; i < (row + 1)*column; i=i+2)
	 //{
	 //	char str[60];
	 //	sprintf(str, "pronunciation/%s.mp3", result[i]);
	 //	SimpleAudioEngine::getInstance()->preloadEffect(str);
	 //}
	 //输出查询的数据
	 //for (i = 0; i < 500; i++)
	 //{
	 //	
	 //		log("result[%d]=%s\n", i, result[i]);
	 //    
	 //}
	 //sqlite3_free_table(result);//释放result的内存空间

	 //#ifdef _DEBUG_ //如果前面已经定义了_DEBUG_ ，则输出所创建的表存在的信息
	 //	printf("zErrMsg=%s\n", zErrMsg);//保留错误信息，如为空(null),表明在执行过程中没有错误信息
	 //#endif
	 sqlite3_close(db);               //关闭数据库
	 finshflag = true;
	 return true;
 }
 void PreLoad::onEnterTransitionDidFinish()
 {
	
	 
}
 void PreLoad::loadMusic()
 {
	// SimpleAudioEngine::getInstance()->preloadEffect("pronunciation/abandon.mp3");
}
 void PreLoad::progressupdate(float dt)
 {
	 if (finshflag)
	 {
		 if (LEVEL == -1)
		 {
			 LEVEL = 1;
			 UserDefault::getInstance()->setIntegerForKey("gold", 0);
			 UserDefault::getInstance()->setIntegerForKey("score", 0);
		 }
		 if (LEVEL > MAXLEVEL)
			 LEVEL = 1;
		 TransitionCrossFade* fade = TransitionCrossFade::create(0.5, GameScene2::createScene(LEVEL,type));
		 Director::getInstance()->replaceScene(fade);
	 }
 }