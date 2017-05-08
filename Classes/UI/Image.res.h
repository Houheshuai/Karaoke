#ifndef _IMAGE_RES_H_
#define _IMAGE_RES_H_

#define NONE_IMG 0x2381
static const int National_Flag_ID[]={
	/*NULL Chinese	NULL	NULL	English	 NULL	Korean	Vietnam	*/
		0,	0x2381,		0,		0,		0x2382,		0,  0x2389,  0x2392,
	/* Thai 	NULL  		Brazil 	Spanish   Tagalog	Italian	Germany	French	*/
	0x2390,	0,	  		0, 		0x238f, 0x238c,	0x2387, 0x2384, 0x2383,
	/*Portuguese NULL	Indonesian	Japanese	Russian	Dutch	Hindi	NULL	*/
	  0x238d,	0,			0x2386, 0x2388,	0x238e,	NONE_IMG, 0x2385, 0,
	/*Persian Hebrew 	Polish 	NULL 	Bhajan 	Malaysia 	NULL 	NULL 	*/
	NONE_IMG, NONE_IMG,	NONE_IMG, 0,	NONE_IMG, 0x238a, 0,		0,
	/*NULL 	NULL	NULL	Mongolian	Arabic	Turkish	NULL	Garba	*/
		0,	0,		0,		0x238b,		0x2380,	0x2391, 0,		0x23a2,
	/*Gujarati  Malayalam	Marathi	  Tamil	  Telugu	    Bengali  Kannada   Sinhala	*/
	 0x23a3, 0x23a6,   0x23a7,  0x23aa,	 0x23ab,  0x23a0, 0x23a4,  0x23a9,
	/*Konkani   Urdu	       Punjabi	    translate	Nepail	   Bhojpuri*/
	0x23a5,   NONE_IMG, NONE_IMG, NONE_IMG, NONE_IMG, 0x23a1
};

//pic for form
//Common
#define bottomItem_ImageNum 0x253c // item bottom BG Pic
#define bottomItem_ImageNum_short 0x253f //setup_title bottom BG Pic

//FormMain
#define pageshow_FirstPicNum 0x2503 // initialization pageShow : Hindi pic = >0x2503

enum{
    IMAGE_ID_SmallPic_record = 0x2500,
    IMAGE_ID_SmallPic_number = 0x2501,
    IMAGE_ID_SmallPic_languages = 0x2502,
    IMAGE_ID_SmallPic_hindi = 0x2503,
    IMAGE_ID_SmallPic_singer = 0x2504,
    IMAGE_ID_SmallPic_program = 0x2505,
    IMAGE_ID_SmallPic_favorite = 0x2506,
    IMAGE_ID_SmallPic_setup = 0x2507,
    IMAGE_ID_SmallPic_manual = 0,
    IMAGE_ID_SmallPic_album = 0x2509,
    IMAGE_ID_SmallPic_game = 0x250a,
    IMAGE_ID_SmallPic_download = 0,

};

//FormPlay
#define picNum_SingerFrame 0x2598
#define picNum_AlbumFrame 0x259c

//FormGameMain
enum{
    IMAGE_ID_Game_SNAKE = 0x25a0,
    IMAGE_ID_Game_BINGO = 0x25a1,
    IMAGE_ID_Game_SOKOBAN = 0x25a2,
    IMAGE_ID_Game_RINGER = 0x25a3,
    IMAGE_ID_Game_BG = 0x25a4,
};

//list form song type image
enum{
	IMAGE_ID_MUKMidi = 0x2554,
	IMAGE_ID_MUKKSC = 0x2555,
	IMAGE_ID_OKF = 0x2556,
	IMAGE_ID_MTV = 0x2557,
	IMAGE_ID_MP3 = 0x2558,
};
//play form PlayBar Status
enum{
	IMAGE_ID_Pause = 0x2661,
	IMAGE_ID_Play = 0x2660,
	IMAGE_ID_RecordOff = 0x2662,
	IMAGE_ID_RecordOn = 0x2663,
	IMAGE_ID_VocalOff = 0x2664,
	IMAGE_ID_VocalOn = 0x2665,
	IMAGE_ID_MelodyOff = 0x2666,
	IMAGE_ID_MelodyOn = 0x2667,

};
//play form buttom
/*
enum{
	IMAGE_ID_Buttom_KSC = 0x2467,     // MUK - KSC
	IMAGE_ID_Buttom_MIDI = 0x2468,	  // MUK - MIDI
	IMAGE_ID_Buttom_MP3 = 0x2469,	  // .MP3
	IMAGE_ID_Buttom_MTV = 0x246a,	  // Video  .avi .mtv
	IMAGE_ID_Buttom_REC = 0x246b,     // .REC
};
*/
enum{
	IMAGE_ID_BtmHint_PAUSE = 0x2720,
	IMAGE_ID_BtmHint_RECORD = 0x2721,
	IMAGE_ID_BtmHint_VOCAL = 0x2722,
	IMAGE_ID_BtmHint_MELODY = 0x2723,
	IMAGE_ID_BtmHint_VOLUME = 0x2724,
};


//FormTunning
//tunning Bar Value
enum{
	IMAGE_ID_TunningBar_Start = 0x2680, //Min_Vol
    IMAGE_ID_TunningBar_End = 0x268c, // Max_Vol
	IMAGE_ID_Tunning_Unfocus_BG = 0x2671,
	IMAGE_ID_Tunning_Focus_BG = 0x2670,
};

//FormScore
//Score分数评价的图片编号
//score Assessment
enum{
    IMAGE_ID_Assessment_Single_excellent = 0x2710,
    IMAGE_ID_Assessment_Single_perfect = 0x2711,
    IMAGE_ID_Assessment_Single_good = 0x2712,
    IMAGE_ID_Assessment_Single_poor = 0x2713,
    IMAGE_ID_Assessment_PK_excellent = 0x2714,
    IMAGE_ID_Assessment_PK_perfect = 0x2715,
    IMAGE_ID_Assessment_PK_good = 0x2716,
    IMAGE_ID_Assessment_PK_poor = 0x2717,

};
// 0~9--ImageNum(2690~2699)
enum{
    IMAGW_ID_Score_Number_0 = 0x2690,
    IMAGW_ID_Score_Number_1 = 0x2691,
    IMAGW_ID_Score_Number_2 = 0x2692,
    IMAGW_ID_Score_Number_3 = 0x2693,
    IMAGW_ID_Score_Number_4 = 0x2694,
    IMAGW_ID_Score_Number_5 = 0x2695,
    IMAGW_ID_Score_Number_6 = 0x2696,
    IMAGW_ID_Score_Number_7 = 0x2697,
    IMAGW_ID_Score_Number_8 = 0x2698,
    IMAGW_ID_Score_Number_9 = 0x2699,

};

//FormSearch
//searchType
enum{
    IMAGE_ID_SearchType_unfocus_Start = 0x2700, // type未选中最左边的选项框的图片编号
    IMAGE_ID_SearchType_unfocus_End = 0x2704, // type未选中最右边的选项框的图片编号
	IMAGE_ID_SearchType_focus_Start = 0x2705, // type选中最左边的选项框的图片编号
	IMAGE_ID_SearchType_focus_End = 0x2709, // type选中最右边的选项框的图片编号.
};
//searchTypeImage
enum{
 	IMAGE_ID_SearchType_Unfocus_favorite = 0x2700,
 	IMAGE_ID_SearchType_Unfocus_number = 0x2701,
 	IMAGE_ID_SearchType_Unfocus_title = 0x2702,
 	IMAGE_ID_SearchType_Unfocus_singer = 0x2703,
 	IMAGE_ID_SearchType_Unfocus_program = 0x2704,
 	IMAGE_ID_SearchType_Focus_favorite = 0x2705,
 	IMAGE_ID_SearchType_Focus_number = 0x2706,
 	IMAGE_ID_SearchType_Focus_title = 0x2707,
 	IMAGE_ID_SearchType_Focus_singer = 0x2708,
 	IMAGE_ID_SearchType_Focus_program = 0x2709

};


#endif
