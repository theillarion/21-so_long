#ifndef INC_21_SO_LONG_IMAGES_H
#define INC_21_SO_LONG_IMAGES_H

enum e_images_main
{
	ImageIdle,
	ImageWall,
	ImageCollectible,
	ImageExit,
	ImageEnemy,
	ImageStartPosition,
	CountImagesMain
};

enum e_images_destroy
{
	ImageDestroy0,
	ImageDestroy1,
	ImageDestroy2,
	ImageDestroy3,
	ImageDestroy4,
	ImageDestroy5,
	ImageDestroy6,
	ImageDestroy7,
	ImageDestroy8,
	CountImagesDestroy
};

enum e_images_score
{
	ImageScore0,
	ImageScore1,
	ImageScore2,
	ImageScore3,
	ImageScore4,
	ImageScore5,
	ImageScore6,
	ImageScore7,
	ImageScore8,
	ImageScore9,
	ImageScoreWord,
	ImageScoreIdle,
	ImageScoreGameOver,
	CountImagesScore,
	HeightImageNumber	= 16,
	WidthImageNumber	= 16,
	HeightImageWord		= 16,
	WidthImageWord		= 80
};

#endif //INC_21_SO_LONG_IMAGES_H
