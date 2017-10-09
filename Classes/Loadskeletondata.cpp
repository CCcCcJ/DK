#include"Loadskeletondata.h"
//英雄骨骼
 spSkeletonData* loadskeletondata::hero_skeletonData0 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData0 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData1 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData1 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData2 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData2 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData3 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData3 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData4 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData4 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData5 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData5 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData6 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData6 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData7 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData7 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData8 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData8 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData9 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData9 = NULL;
 spSkeletonData* loadskeletondata::hero_skeletonData10 = NULL;
 spAnimationStateData* loadskeletondata::hero_stateData10 = NULL;
 //怪物骨骼
 spSkeletonData* loadskeletondata::monster_skeletonData0 = NULL;
 spAnimationStateData* loadskeletondata::monster_stateData0 = NULL; 
 spSkeletonData* loadskeletondata::monster_skeletonData1 = NULL;
 spAnimationStateData* loadskeletondata::monster_stateData1 = NULL;
 spSkeletonData* loadskeletondata::monster_skeletonData2 = NULL;
 spAnimationStateData* loadskeletondata::monster_stateData2 = NULL;
 spSkeletonData* loadskeletondata::monster_skeletonData3 = NULL;
 spAnimationStateData* loadskeletondata::monster_stateData3 = NULL;
 spSkeletonData* loadskeletondata::monster_skeletonData4 = NULL;
 spAnimationStateData* loadskeletondata::monster_stateData4 = NULL;
 loadskeletondata* loadskeletondata::instance;
 loadskeletondata * loadskeletondata::getInstance()
 {
	 if (instance == NULL)
	 {
		 instance = new loadskeletondata();
		 loadFrame();

	 }

	 return instance;
 }
void loadskeletondata::loadFrame()
{
	//英雄0骨骼动画加载
	spAtlas* _atlas = spAtlas_createFromFile("skeletal/a.atlas", 0);

	CCASSERT(_atlas, "Error reading atlas file.");

	// This attachment loader configures attachments with data needed for cocos2d-x rendering.
	// Do not dispose the attachment loader until the skeleton data is disposed!
	/*_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);*/
	spAttachmentLoader* _attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//
																										//// Load the skeleton data.
																										//加载骨骼
	spSkeletonJson* json = spSkeletonJson_createWithLoader(_attachmentLoader);//
																			  //spSkeletonJson* json = spSkeletonJson_create(_atlas);
	json->scale = 0.1f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData0 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/a.json");
	CCASSERT(hero_skeletonData0, json->error ? json->error : "Error reading skeleton data file.");

	spSkeletonJson_dispose(json);

	//// Setup mix times.
	hero_stateData0 = spAnimationStateData_create(hero_skeletonData0);
	spAnimationStateData_setMixByName(hero_stateData0, "walk", "attack", 0.2f);
	//spAnimationStateData_setMixByName(hero_stateData0, "attacking", "flying", 0.2f);
	//英雄1骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/b.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData1 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/b.json");
	CCASSERT(hero_skeletonData1, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData1 = spAnimationStateData_create(hero_skeletonData1);
	spAnimationStateData_setMixByName(hero_stateData1, "walk", "attack", 0.2f);
	//英雄2骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/i.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData2 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/i.json");
	CCASSERT(hero_skeletonData2, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData2 = spAnimationStateData_create(hero_skeletonData2);
	spAnimationStateData_setMixByName(hero_stateData2, "walk", "attack", 0.2f);
	//英雄3骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/c.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData3 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/c.json");
	CCASSERT(hero_skeletonData3, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData3 = spAnimationStateData_create(hero_skeletonData3);
	spAnimationStateData_setMixByName(hero_stateData3, "walk", "attack", 0.2f);
	//英雄4骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/g.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData4 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/g.json");
	CCASSERT(hero_skeletonData4, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData4 = spAnimationStateData_create(hero_skeletonData4);
	spAnimationStateData_setMixByName(hero_stateData4, "walk", "attack", 0.2f);
	//英雄n骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/n.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData5 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/n.json");
	CCASSERT(hero_skeletonData5, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData5 = spAnimationStateData_create(hero_skeletonData5);
	spAnimationStateData_setMixByName(hero_stateData5, "walk", "attack", 0.2f);
	//英雄p骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/p.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData6 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/p.json");
	CCASSERT(hero_skeletonData6, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData6 = spAnimationStateData_create(hero_skeletonData6);
	spAnimationStateData_setMixByName(hero_stateData6, "walk", "attack", 0.2f);
	//英雄m骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/m.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData7 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/m.json");
	CCASSERT(hero_skeletonData7, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData7 = spAnimationStateData_create(hero_skeletonData7);
	spAnimationStateData_setMixByName(hero_stateData7, "walk", "attack", 0.2f);
	//英雄u骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/u.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData8 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/u.json");
	CCASSERT(hero_skeletonData8, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData8 = spAnimationStateData_create(hero_skeletonData8);
	spAnimationStateData_setMixByName(hero_stateData8, "walk", "attack", 0.2f);
	//英雄f骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/f.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData9 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/f.json");
	CCASSERT(hero_skeletonData9, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData9 = spAnimationStateData_create(hero_skeletonData9);
	//英雄o骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/o.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	hero_skeletonData10 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/o.json");
	CCASSERT(hero_skeletonData10, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	hero_stateData10 = spAnimationStateData_create(hero_skeletonData10);
	//怪物0骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/one.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	monster_skeletonData0 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/one.json");
	CCASSERT(monster_skeletonData0, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	monster_stateData0 = spAnimationStateData_create(monster_skeletonData0);
	spAnimationStateData_setMixByName(monster_stateData0, "walk", "attack", 0.2f);
	//怪物1骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/5.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	monster_skeletonData1 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/5.json");
	CCASSERT(monster_skeletonData1, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	monster_stateData1 = spAnimationStateData_create(monster_skeletonData1);
	spAnimationStateData_setMixByName(monster_stateData1, "walk", "attack", 0.2f);
	//怪物2骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/3.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	monster_skeletonData2 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/3.json");
	CCASSERT(monster_skeletonData2, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	monster_stateData2 = spAnimationStateData_create(monster_skeletonData2);
	spAnimationStateData_setMixByName(monster_stateData2, "walk", "attack", 0.2f);
	//怪物3骨骼动画加载
	_atlas = spAtlas_createFromFile("skeletal/2.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	monster_skeletonData3 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/2.json");
	CCASSERT(monster_skeletonData3, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	monster_stateData3 = spAnimationStateData_create(monster_skeletonData3);
	spAnimationStateData_setMixByName(monster_stateData3, "walk", "attack", 0.2f);
	//怪物4动画加载
	_atlas = spAtlas_createFromFile("skeletal/6.atlas", 0);
	CCASSERT(_atlas, "Error reading atlas file.");
	_attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);//加载骨骼																			
	json = spSkeletonJson_createWithLoader(_attachmentLoader);//spSkeletonJson* json = spSkeletonJson_create(_atlas);									  
	json->scale = 0.05f; // Resizes skeleton data to 60% of the size it was in Spine.
	monster_skeletonData4 = spSkeletonJson_readSkeletonDataFile(json, "skeletal/6.json");
	CCASSERT(monster_skeletonData4, json->error ? json->error : "Error reading skeleton data file.");
	spSkeletonJson_dispose(json);
	// Setup mix times.
	monster_stateData4 = spAnimationStateData_create(monster_skeletonData4);
	spAnimationStateData_setMixByName(monster_stateData4, "walk", "attack", 0.2f);
}
loadskeletondata::~loadskeletondata()
{
	spSkeletonData_dispose(hero_skeletonData0);
	spAnimationStateData_dispose(hero_stateData0);
	spSkeletonData_dispose(hero_skeletonData1);
	spAnimationStateData_dispose(hero_stateData1);
	spSkeletonData_dispose(hero_skeletonData2);
	spAnimationStateData_dispose(hero_stateData2);
	spSkeletonData_dispose(hero_skeletonData3);
	spAnimationStateData_dispose(hero_stateData3);
	spSkeletonData_dispose(hero_skeletonData4);
	spAnimationStateData_dispose(hero_stateData4);
	spSkeletonData_dispose(hero_skeletonData5);
	spAnimationStateData_dispose(hero_stateData5);
	spSkeletonData_dispose(hero_skeletonData6);
	spAnimationStateData_dispose(hero_stateData6);
	spSkeletonData_dispose(hero_skeletonData7);
	spAnimationStateData_dispose(hero_stateData7);
	spSkeletonData_dispose(hero_skeletonData8);
	spAnimationStateData_dispose(hero_stateData8);
	spSkeletonData_dispose(hero_skeletonData9);
	spAnimationStateData_dispose(hero_stateData9);
	spSkeletonData_dispose(hero_skeletonData10);
	spAnimationStateData_dispose(hero_stateData10);

	spSkeletonData_dispose(monster_skeletonData0);
	spAnimationStateData_dispose(monster_stateData0);
	spSkeletonData_dispose(monster_skeletonData1);
	spAnimationStateData_dispose(monster_stateData1);
	spSkeletonData_dispose(monster_skeletonData2);
	spAnimationStateData_dispose(monster_stateData2);
	spSkeletonData_dispose(monster_skeletonData3);
	spAnimationStateData_dispose(monster_stateData3);
	spSkeletonData_dispose(monster_skeletonData4);
	spAnimationStateData_dispose(monster_stateData4);
	instance = NULL;
}