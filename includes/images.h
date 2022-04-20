/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:55:28 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:55:29 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_H
# define IMAGES_H

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

#endif
