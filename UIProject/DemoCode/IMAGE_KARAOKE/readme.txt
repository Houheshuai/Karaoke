Image split & merge使用方法：

D:\>mergePNG.exe
Image split & merge V1.02

;==================================================================================
split small png from Image.txt and big png files
  split usage: mergePNG  -S  c:\path\Images.txt
  split usage: mergePNG  -S  Images.txt
  split only IMAGEFILE 0x180A usage: mergePNG  -S -o 180A  Images.txt
  split ignore IMAGEFILE 0x180A 0x180B usage: mergePNG  -S -i 180A -i 180B  Images.txt

;==================================================================================
merge small png to  big png files, and update postion in Image.txt
  merge usage: mergePNG  -M  c:\path\Images.txt
  merge usage: mergePNG  -M  Images.txt
  merge only IMAGEFILE 0x180A usage: mergePNG  -M -o 180A  Images.txt
  merge ignore IMAGEFILE 0x180A 0x180B usage: mergePNG  -M -i 180A -i 180B Images.txt
;==================================================================================

  (1.01)merge with same position usage: mergePNG  -M -F Images.txt
  (1.01)spilt and merge usage: mergePNG  -S -M  Images.txt
  (1.02)merge with other width/height usage: mergePNG  -M -W 512 Images.txt

;==================================================================================
-i参数：可以忽略处理多个合并图片， 
-o参数：只处理一个合并图片。
-F参数：对于那些密密麻麻的合图，可以增加一种模式， 不变动图片的位置，只是合并，用于修改，增加，减少图片内容， 注意增加时候写上左上角位置。
-W参数：指定合图尺寸，比图 512 X 512 图片，使用参数 -W 512

;==================================================================================
一般处理过程：
;----------------------------------------------------------------------------------
1. 分离图片
	分离图片时候，如果目标文件存在，可以选择是否覆盖文件， yes, no, all.

	Images.txt 处理前：
	IMAGEFILE 0x1801 "png/homebg.png"
	IMAGE   0x2000	(0x1801,	0.0000	,	0.0000	,	1.0000	,	0.7500) //homebg
	IMAGE   0x2001	(0x1802,	0.0000	,	0.0000	,	0.1807	,	0.2529) //bookcase

;----------------------------------------------------------------------------------
2. 修改分离图片文件的内容， 改变大小等

;----------------------------------------------------------------------------------
3. 增加， 减少，移动图片
	方法：增加减少在Images.txt文件里面的行 
		 IMAGE   0x2000	(0x1801,	0.0000	,	0.0000	,	1.0000	,	0.7500) //homebg
		 
	注意：
		1. IMAGEFILE ID 0x1801， 和图片放的目录对应
		2. 文件名和 IMAGE ID 0x2000 对应
		3. 修改注释有效， 修改坐标无效
	
;----------------------------------------------------------------------------------
4. 移动一个小图片，从一个大图到另一个大图
	1. 修改Images.txt文件：
		IMAGEFILE 0x1801 "png/homebg.png"
		IMAGEFILE 0x1802 "png/home.png"
		IMAGE 0x2000 (0x1801, 0.0000 , 0.0000 , 1.0000 , 0.7500) //homebg
		IMAGE 0x2001 (0x1802, 0.0000 , 0.0000 , 0.1807 , 0.2529) //bookcase
		
		--》
		IMAGE 0x2000 (0x1801, 0.0000 , 0.0000 , 1.0000 , 0.7500) //homebg
		IMAGE 0x2001 (0x1801, 0.0000 , 0.0000 , 0.1807 , 0.2529) //bookcase -- move from homebg.png to home.png 
		
	
	2. 移动图片  png/homebg/2001.png 到  png/home/2001.png
	
	注意：移动图片的时候，最好不要用-F参数， 否则请检查是否重叠图片。
				如果改变IMAGE ID 2001, 需要对应的修改文件名。


;----------------------------------------------------------------------------------
5. 合并，生产新的Images.txt和合并的png文件
Images.txt 处理后：
IMAGEFILE 0x1801 "png/homebg.png"
IMAGE   0x2000 (0x1801, 0.0000 , 0.0000 , 1.0000 , 0.5000) //homebg -- 修改图片高度引起

注意:合并时候的ERROR报错，图片超出1024 * 1024范围的时候会报错。遇到此类错误，请修改图片，再次合并。 


只是某几个PNG(1802, 180D)固定位置，批处理写法：
mergePNG  -M -o 1801  Images.txt
copy new\images.txt Images_t.txt
mergePNG  -M -o 1802  Images_t.txt  -F
copy new\images.txt Images_t.txt
mergePNG  -M -o 1803  Images_t.txt
copy new\images.txt Images_t.txt
mergePNG  -M -o 180C  Images_t.txt
copy new\images.txt Images_t.txt
mergePNG  -M -o 180D  Images_t.txt  -F
copy new\images.txt Images_t.txt
mergePNG  -M -o 180E  Images_t.txt
copy new\images.txt Images_t.txt
mergePNG  -M -o 180F  Images_t.txt
