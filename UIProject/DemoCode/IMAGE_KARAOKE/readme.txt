Image split & mergeʹ�÷�����

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
-i���������Ժ��Դ������ϲ�ͼƬ�� 
-o������ֻ����һ���ϲ�ͼƬ��
-F������������Щ��������ĺ�ͼ����������һ��ģʽ�� ���䶯ͼƬ��λ�ã�ֻ�Ǻϲ��������޸ģ����ӣ�����ͼƬ���ݣ� ע������ʱ��д�����Ͻ�λ�á�
-W������ָ����ͼ�ߴ磬��ͼ 512 X 512 ͼƬ��ʹ�ò��� -W 512

;==================================================================================
һ�㴦����̣�
;----------------------------------------------------------------------------------
1. ����ͼƬ
	����ͼƬʱ�����Ŀ���ļ����ڣ�����ѡ���Ƿ񸲸��ļ��� yes, no, all.

	Images.txt ����ǰ��
	IMAGEFILE 0x1801 "png/homebg.png"
	IMAGE   0x2000	(0x1801,	0.0000	,	0.0000	,	1.0000	,	0.7500) //homebg
	IMAGE   0x2001	(0x1802,	0.0000	,	0.0000	,	0.1807	,	0.2529) //bookcase

;----------------------------------------------------------------------------------
2. �޸ķ���ͼƬ�ļ������ݣ� �ı��С��

;----------------------------------------------------------------------------------
3. ���ӣ� ���٣��ƶ�ͼƬ
	���������Ӽ�����Images.txt�ļ�������� 
		 IMAGE   0x2000	(0x1801,	0.0000	,	0.0000	,	1.0000	,	0.7500) //homebg
		 
	ע�⣺
		1. IMAGEFILE ID 0x1801�� ��ͼƬ�ŵ�Ŀ¼��Ӧ
		2. �ļ����� IMAGE ID 0x2000 ��Ӧ
		3. �޸�ע����Ч�� �޸�������Ч
	
;----------------------------------------------------------------------------------
4. �ƶ�һ��СͼƬ����һ����ͼ����һ����ͼ
	1. �޸�Images.txt�ļ���
		IMAGEFILE 0x1801 "png/homebg.png"
		IMAGEFILE 0x1802 "png/home.png"
		IMAGE 0x2000 (0x1801, 0.0000 , 0.0000 , 1.0000 , 0.7500) //homebg
		IMAGE 0x2001 (0x1802, 0.0000 , 0.0000 , 0.1807 , 0.2529) //bookcase
		
		--��
		IMAGE 0x2000 (0x1801, 0.0000 , 0.0000 , 1.0000 , 0.7500) //homebg
		IMAGE 0x2001 (0x1801, 0.0000 , 0.0000 , 0.1807 , 0.2529) //bookcase -- move from homebg.png to home.png 
		
	
	2. �ƶ�ͼƬ  png/homebg/2001.png ��  png/home/2001.png
	
	ע�⣺�ƶ�ͼƬ��ʱ����ò�Ҫ��-F������ ���������Ƿ��ص�ͼƬ��
				����ı�IMAGE ID 2001, ��Ҫ��Ӧ���޸��ļ�����


;----------------------------------------------------------------------------------
5. �ϲ��������µ�Images.txt�ͺϲ���png�ļ�
Images.txt �����
IMAGEFILE 0x1801 "png/homebg.png"
IMAGE   0x2000 (0x1801, 0.0000 , 0.0000 , 1.0000 , 0.5000) //homebg -- �޸�ͼƬ�߶�����

ע��:�ϲ�ʱ���ERROR����ͼƬ����1024 * 1024��Χ��ʱ��ᱨ����������������޸�ͼƬ���ٴκϲ��� 


ֻ��ĳ����PNG(1802, 180D)�̶�λ�ã�������д����
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
