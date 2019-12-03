#include <iostream>                                                                              
#include <omp.h>           
#include "pch.h"
#include "stdio.h"
#include <time.h>

void swapAscendente(int index1, int index2, int *vetor)                                           //swap two values such that they appear in ascending order in the array
{
	if (vetor[index2] < vetor[index1])
	{
		int temp = vetor[index2];
		vetor[index2] = vetor[index1];
		vetor[index1] = temp;
	}
}
void swapDescendente(int index1, int index2, int *vetor)                                           //swap two values such that they appear in decending order in the array
{
	if (vetor[index1] < vetor[index2])
	{
		int temp = vetor[index2];
		vetor[index2] = vetor[index1];
		vetor[index1] = temp;
	}
}
void bitonicSortFromBitonicSequence(int startIndex, int lastIndex, int dir, int *vetor)     //form a increaseing or decreasing array when a bitonic input is given to the function
{
	if (dir == 1)
	{
		int counter = 0;                                                                    //counter to keep track of already swapped elements ,, parallelising this area results in poor performance due to overhead ,,need to fix
		int noOfElements = lastIndex - startIndex + 1;
		for (int j = noOfElements / 2; j > 0; j = j / 2)
		{
			counter = 0;
			for (int i = startIndex; i + j <= lastIndex; i++)
			{
				if (counter < j)
				{
					swapAscendente(i, i + j, vetor);
					counter++;

				}
				else
				{
					counter = 0;
					i = i + j - 1;

				}
			}
		}
	}
	else                                                                                  
	{
		int counter = 0;
		int noOfElements = lastIndex - startIndex + 1;
		for (int j = noOfElements / 2; j > 0; j = j / 2)
		{
			counter = 0;
			for (int i = startIndex; i <= (lastIndex - j); i++)
			{
				if (counter < j)
				{
					swapDescendente(i, i + j, vetor);
					counter++;

				}
				else
				{
					counter = 0;
					i = i + j - 1;

				}
			}
		}
	}

}
void bitonicSequenceGenerator(int startIndex, int lastIndex, int *ar)                         
{
	int noOfElements = lastIndex - startIndex + 1;
	for (int j = 2; j <= noOfElements; j = j * 2)
	{
#pragma omp parallel for                                                        
		for (int i = 0; i < noOfElements; i = i + j)
		{
			if (((i / j) % 2) == 0)                                                               
			{
				bitonicSortFromBitonicSequence(i, i + j - 1, 1, ar);
			}
			else
			{
				bitonicSortFromBitonicSequence(i, i + j - 1, 0, ar);
			}
		}
	}
}
int main()                                                                                        //main driver function
{
	                    
	int vetor[1024] = { 564, 689, 913, 377, 792, 951, 107, 631, 287, 326, 295, 460, 493, 410, 254, 828, 389, 434, 342, 573, 950, 84, 516, 340, 621, 806, 330, 89, 253, 29, 682, 269, 459, 758, 420, 227, 6, 327, 896, 760, 806, 93, 328, 711, 472, 408, 494, 459, 343, 249, 223, 243, 543, 719, 78, 267, 216, 553, 110, 900, 409, 864, 101, 278, 284, 242, 475, 282, 58, 545, 162, 725, 619, 891, 147, 765, 1000, 680, 82, 268, 608, 883, 597, 462, 25, 673, 248, 659, 1018, 120, 538, 965, 310, 975, 169, 482, 966, 547, 27, 774, 307, 352, 606, 29, 688, 534, 846, 475, 559, 560, 379, 932, 421, 378, 43, 765, 764, 244, 756, 658, 574, 957, 939, 363, 369, 784, 786, 854, 49, 605, 1013, 275, 879, 334, 554, 985, 256, 607, 406, 284, 69, 40, 160, 693, 659, 498, 479, 21, 731, 485, 797, 217, 182, 606, 259, 588, 971, 242, 968, 852, 72, 147, 22, 324, 621, 190, 198, 458, 395, 674, 253, 72, 252, 310, 396, 829, 397, 320, 1010, 675, 561, 720, 815, 253, 694, 262, 321, 757, 815, 691, 0, 996, 775, 303, 480, 251, 89, 504, 262, 1004, 741, 971, 1010, 546, 161, 710, 863, 43, 258, 381, 131, 612, 939, 965, 326, 631, 475, 968, 893, 50, 156, 600, 232, 885, 60, 497, 748, 473, 567, 181, 364, 877, 669, 976, 944, 391, 57, 178, 26, 322, 570, 274, 157, 942, 186, 637, 798, 82, 846, 845, 877, 263, 856, 467, 384, 102, 144, 326, 674, 427, 258, 387, 218, 828, 993, 271, 920, 304, 617, 702, 436, 356, 736, 824, 841, 94, 248, 161, 244, 430, 137, 922, 374, 451, 16, 307, 820, 944, 854, 427, 507, 169, 491, 765, 283, 560, 855, 893, 245, 705, 103, 892, 577, 241, 105, 993, 376, 584, 833, 455, 237, 680, 520, 370, 992, 774, 638, 791, 639, 912, 153, 641, 405, 907, 468, 732, 464, 619, 757, 117, 252, 368, 119, 510, 427, 633, 416, 558, 250, 1022, 144, 16, 65, 100, 437, 782, 153, 16, 409, 640, 144, 564, 75, 734, 944, 802, 149, 22, 80, 758, 967, 843, 104, 156, 438, 108, 568, 332, 782, 409, 135, 1020, 648, 752, 640, 361, 335, 272, 239, 403, 761, 243, 611, 809, 536, 349, 416, 743, 449, 840, 14, 872, 765, 679, 885, 919, 793, 778, 295, 540, 714, 979, 466, 147, 197, 787, 947, 367, 611, 712, 939, 19, 196, 281, 831, 564, 837, 810, 816, 719, 247, 393, 342, 604, 275, 787, 934, 519, 170, 72, 168, 978, 692, 965, 711, 802, 911, 459, 19, 644, 1013, 178, 946, 99, 132, 1001, 609, 590, 209, 580, 536, 312, 724, 323, 847, 748, 601, 502, 617, 1023, 621, 787, 752, 510, 566, 559, 365, 946, 710, 55, 190, 304, 263, 530, 773, 432, 932, 317, 150, 438, 737, 937, 803, 858, 485, 784, 220, 493, 281, 681, 22, 377, 940, 989, 108, 1011, 266, 872, 583, 53, 477, 803, 705, 1007, 18, 937, 534, 678, 123, 211, 308, 986, 364, 785, 75, 772, 5, 929, 412, 979, 88, 880, 941, 578, 744, 436, 229, 648, 522, 595, 475, 748, 384, 435, 626, 466, 374, 559, 30, 0, 78, 252, 339, 615, 902, 870, 12, 495, 157, 555, 224, 818, 724, 835, 538, 243, 164, 155, 949, 164, 909, 325, 395, 1003, 1000, 501, 926, 761, 994, 756, 848, 0, 725, 227, 438, 30, 853, 605, 1016, 392, 994, 754, 669, 508, 558, 304, 237, 462, 344, 39, 172, 770, 491, 387, 290, 82, 255, 382, 718, 467, 988, 628, 356, 846, 304, 88, 577, 506, 48, 361, 1019, 864, 1023, 529, 686, 315, 575, 394, 747, 886, 35, 514, 955, 191, 909, 906, 331, 839, 260, 881, 629, 666, 29, 267, 475, 944, 481, 842, 60, 593, 56, 194, 515, 2, 571, 173, 292, 659, 213, 80, 678, 332, 970, 390, 661, 723, 187, 890, 552, 249, 394, 267, 763, 647, 1007, 583, 824, 316, 988, 546, 641, 326, 368, 121, 202, 317, 390, 145, 762, 939, 301, 855, 293, 881, 826, 106, 68, 12, 251, 710, 890, 292, 885, 172, 911, 64, 518, 472, 625, 383, 821, 393, 471, 514, 169, 708, 965, 139, 504, 752, 144, 1014, 217, 548, 531, 360, 607, 161, 389, 552, 222, 732, 646, 931, 382, 495, 299, 441, 907, 477, 703, 1021, 110, 275, 565, 920, 183, 754, 259, 298, 895, 706, 969, 332, 512, 93, 668, 992, 835, 736, 51, 940, 1007, 645, 930, 25, 840, 714, 661, 672, 1008, 833, 128, 423, 661, 784, 582, 142, 634, 348, 988, 913, 145, 338, 250, 143, 639, 501, 1024, 639, 262, 876, 634, 856, 260, 365, 314, 838, 579, 614, 575, 170, 100, 471, 131, 182, 475, 109, 948, 168, 730, 487, 595, 263, 404, 641, 247, 106, 1005, 64, 846, 624, 990, 139, 364, 257, 1005, 64, 910, 306, 847, 630, 153, 694, 891, 256, 877, 767, 50, 885, 840, 447, 533, 644, 398, 867, 254, 328, 183, 701, 851, 516, 870, 202, 863, 185, 706, 397, 247, 580, 126, 911, 924, 968, 701, 970, 434, 784, 37, 684, 727, 971, 663, 868, 340, 170, 199, 317, 128, 140, 401, 259, 582, 464, 593, 596, 176, 303, 979, 304, 71, 948, 395, 979, 863, 408, 954, 590, 303, 263, 946, 165, 180, 998, 231, 797, 751, 812, 475, 279, 1020, 392, 700, 740, 503, 310, 156, 223, 477, 820, 208, 291, 898, 137, 491, 728, 972, 882, 553, 400, 813, 462, 532, 820, 563, 518, 875, 49, 152, 254, 453, 979, 31, 686, 838, 364, 860, 408, 942, 649, 500, 317, 10, 459, 237, 430, 226, 49, 795, 843, 68, 912, 48, 23, 878, 646, 1011, 374, 501, 972, 322, 278, 50, 171, 662, 590, 966, 885, 639, 522, 586, 1020, 127, 247, 228, 575, 59, 424, 546, 318, 697, 45, 712, 800, 309, 487, 148, 378, 689, 620, 76, 218, 203, 111, 924, 65, 290, 137, 831, 321, 121, 962, 443, 258, 734, 61, 968, 959, 980, 110, 680, 792, 245, 587, 449, 456, 133, 303, 190, 172, 449, 747, 580, 572 };
	
	clock_t begin = clock();
	
	bitonicSequenceGenerator(0, 1023, vetor);

	clock_t end = clock();
	
	double time_spent1 = (double)end-begin / CLOCKS_PER_SEC;

	int vetor2[1024] = { 464, 492, 142, 356, 666, 656, 412, 653, 53, 732, 300, 79, 708, 372, 316, 517, 890, 558, 167, 384, 59, 42, 142, 255, 688, 214, 1004, 613, 248, 155, 77, 679, 936, 869, 13, 213, 489, 628, 399, 817, 421, 475, 145, 179, 223, 739, 828, 414, 996, 370, 296, 908, 137, 17, 136, 288, 708, 253, 662, 645, 1003, 889, 570, 31, 588, 438, 655, 423, 907, 221, 42, 1006, 448, 439, 790, 393, 55, 130, 391, 376, 660, 365, 753, 46, 389, 268, 673, 836, 785, 557, 267, 1012, 1003, 492, 645, 197, 932, 580, 717, 500, 600, 510, 367, 390, 473, 669, 946, 50, 96, 206, 19, 454, 695, 571, 949, 604, 186, 857, 308, 963, 174, 292, 214, 292, 797, 122, 784, 393, 752, 861, 306, 676, 938, 360, 911, 323, 236, 704, 391, 899, 777, 983, 645, 1010, 798, 34, 1010, 1003, 676, 845, 576, 791, 866, 576, 1022, 617, 734, 769, 89, 497, 996, 373, 271, 8, 400, 84, 600, 606, 117, 998, 563, 642, 769, 795, 93, 38, 331, 943, 475, 924, 551, 669, 131, 210, 532, 763, 133, 293, 148, 453, 1013, 541, 971, 303, 79, 769, 539, 363, 121, 119, 684, 479, 70, 655, 661, 922, 188, 666, 87, 64, 677, 839, 227, 610, 855, 559, 99, 511, 141, 156, 831, 504, 647, 801, 693, 72, 826, 555, 709, 384, 885, 709, 35, 406, 800, 731, 300, 608, 293, 484, 542, 332, 744, 262, 719, 87, 93, 31, 685, 955, 416, 451, 681, 774, 127, 479, 920, 306, 1013, 766, 379, 907, 906, 748, 407, 330, 499, 292, 987, 760, 960, 760, 441, 264, 779, 841, 50, 1009, 948, 315, 257, 913, 1020, 880, 405, 283, 378, 85, 862, 953, 77, 741, 497, 329, 888, 88, 256, 554, 285, 369, 120, 199, 589, 103, 401, 564, 257, 74, 393, 165, 32, 120, 766, 92, 999, 625, 592, 239, 179, 147, 706, 706, 412, 136, 760, 543, 267, 1014, 931, 291, 412, 667, 74, 614, 167, 876, 290, 529, 720, 1, 232, 22, 50, 815, 397, 887, 132, 596, 436, 490, 997, 476, 983, 131, 64, 214, 775, 418, 3, 613, 705, 41, 801, 549, 850, 479, 591, 186, 360, 170, 607, 442, 295, 618, 614, 711, 246, 576, 61, 969, 240, 947, 280, 409, 19, 719, 871, 642, 514, 221, 978, 477, 124, 733, 107, 339, 448, 262, 551, 571, 565, 850, 562, 924, 569, 805, 747, 700, 926, 296, 356, 881, 759, 23, 978, 354, 655, 935, 451, 794, 702, 426, 411, 163, 214, 80, 279, 128, 53, 783, 332, 70, 1011, 23, 69, 957, 922, 851, 555, 335, 597, 469, 14, 850, 632, 874, 938, 634, 876, 92, 221, 204, 443, 359, 813, 282, 2, 537, 329, 583, 597, 481, 842, 936, 279, 44, 4, 470, 640, 585, 150, 215, 368, 183, 947, 868, 479, 592, 142, 48, 270, 144, 243, 172, 207, 59, 369, 450, 334, 660, 919, 73, 380, 563, 629, 489, 129, 748, 964, 662, 560, 719, 51, 559, 725, 148, 620, 618, 743, 392, 976, 35, 289, 599, 1, 345, 493, 772, 112, 425, 436, 611, 869, 48, 459, 216, 171, 588, 409, 430, 258, 1016, 244, 506, 508, 939, 77, 367, 869, 866, 737, 939, 594, 633, 503, 730, 887, 33, 951, 700, 15, 51, 565, 857, 544, 367, 816, 280, 301, 933, 1024, 634, 161, 105, 286, 788, 956, 334, 717, 39, 805, 437, 299, 25, 680, 511, 705, 561, 569, 672, 685, 211, 827, 626, 257, 245, 949, 24, 202, 349, 592, 718, 910, 111, 1020, 776, 999, 1010, 873, 64, 461, 246, 89, 844, 272, 774, 536, 871, 290, 515, 926, 932, 709, 362, 860, 599, 514, 364, 805, 104, 146, 541, 127, 764, 652, 759, 128, 152, 651, 174, 498, 263, 407, 497, 511, 701, 18, 445, 33, 901, 835, 359, 131, 478, 582, 901, 650, 432, 67, 698, 196, 99, 975, 64, 97, 396, 1, 473, 631, 861, 176, 339, 728, 652, 380, 68, 398, 547, 318, 943, 292, 339, 802, 786, 352, 203, 659, 955, 830, 605, 259, 298, 298, 508, 969, 821, 406, 732, 432, 748, 397, 92, 38, 690, 222, 120, 505, 556, 909, 791, 597, 455, 140, 1012, 569, 273, 45, 879, 332, 485, 655, 682, 318, 571, 798, 332, 501, 732, 919, 435, 926, 763, 825, 237, 186, 421, 285, 493, 759, 985, 999, 351, 565, 812, 218, 886, 593, 555, 286, 833, 632, 431, 158, 374, 37, 449, 846, 463, 951, 683, 754, 493, 467, 954, 116, 1006, 143, 727, 71, 421, 486, 560, 48, 502, 558, 44, 302, 223, 1006, 359, 744, 445, 535, 311, 555, 110, 384, 912, 903, 387, 716, 894, 823, 890, 27, 677, 261, 310, 965, 580, 516, 160, 271, 982, 878, 846, 670, 871, 695, 75, 681, 497, 195, 172, 272, 907, 88, 763, 240, 481, 437, 720, 138, 674, 544, 144, 729, 424, 576, 29, 51, 781, 716, 973, 270, 796, 909, 491, 614, 863, 123, 202, 763, 439, 28, 130, 565, 443, 643, 888, 652, 788, 576, 322, 57, 1000, 299, 215, 323, 329, 820, 0, 677, 352, 61, 972, 793, 293, 142, 178, 120, 457, 686, 117, 859, 31, 752, 888, 235, 1017, 33, 662, 265, 298, 123, 960, 520, 395, 696, 458, 359, 261, 173, 417, 488, 145, 731, 1011, 854, 986, 821, 488, 220, 685, 922, 319, 561, 240, 462, 1015, 646, 783, 83, 167, 407, 341, 358, 588, 332, 1007, 910, 745, 736, 904, 614, 99, 738, 806, 979, 323, 52, 155, 405, 123, 346, 602, 543, 438, 422, 329, 96, 246, 343, 716, 846, 827, 407, 764, 86, 573, 803, 211, 148, 673, 672, 277, 530, 212, 818, 354, 610, 156, 25, 1018, 682, 1018, 759, 321, 188, 883, 418, 487, 12, 90, 148, 961, 1010, 552, 281, 546, 39, 114, 175, 769, 388, 481, 141, 114, 925, 362, 617, 426, 283, 884, 749, 82, 547, 271, 760, 627, 958, 578, 914, 656, 478, 675, 225, 154, 785, 717, 204, 235, 466, 951, 216, 476, 692, 336, 296, 593, 556, 237, 369, 1014, 322, 29, 772, 406, 663, 616, 1001, 613, 629, 885 };

	begin = clock();

	bitonicSequenceGenerator(0, 1023, vetor2);

	end = clock();

	double time_spent2 = (double)end - begin / CLOCKS_PER_SEC;

	int vetor3[1024] = { 222, 776, 807, 917, 978, 810, 965, 896, 113, 776, 581, 155, 65, 416, 213, 852, 640, 418, 777, 444, 558, 220, 669, 447, 1024, 339, 741, 772, 265, 491, 979, 568, 762, 235, 888, 897, 964, 965, 503, 9, 132, 60, 675, 562, 102, 516, 80, 584, 694, 796, 932, 435, 840, 686, 184, 175, 505, 473, 619, 583, 485, 284, 322, 799, 889, 700, 961, 822, 668, 833, 38, 85, 28, 324, 348, 58, 177, 749, 301, 560, 23, 15, 546, 6, 350, 976, 499, 369, 163, 559, 881, 976, 290, 393, 891, 583, 817, 170, 704, 0, 669, 93, 203, 491, 717, 475, 537, 894, 845, 633, 920, 950, 351, 334, 177, 28, 478, 850, 701, 226, 369, 696, 251, 1012, 390, 348, 345, 716, 795, 37, 292, 552, 194, 583, 893, 969, 178, 785, 1010, 727, 797, 786, 23, 399, 419, 423, 19, 816, 180, 13, 440, 549, 746, 612, 931, 637, 76, 610, 321, 59, 91, 625, 899, 317, 252, 748, 465, 783, 845, 0, 940, 639, 647, 743, 932, 27, 70, 378, 604, 108, 957, 291, 776, 612, 132, 453, 853, 987, 1004, 91, 857, 28, 303, 566, 986, 948, 62, 284, 269, 628, 117, 592, 462, 874, 263, 666, 309, 56, 831, 103, 800, 810, 22, 305, 697, 963, 661, 628, 439, 728, 583, 11, 518, 491, 382, 1005, 687, 915, 558, 96, 975, 754, 723, 600, 241, 356, 803, 191, 732, 372, 3, 590, 66, 572, 901, 742, 392, 385, 287, 490, 997, 462, 650, 394, 491, 919, 437, 569, 719, 753, 106, 913, 967, 743, 400, 85, 126, 441, 776, 859, 603, 371, 316, 927, 858, 719, 291, 34, 658, 826, 471, 265, 739, 811, 654, 213, 164, 363, 555, 871, 329, 87, 67, 595, 607, 586, 115, 91, 869, 609, 29, 309, 136, 450, 177, 479, 8, 696, 330, 844, 973, 881, 74, 613, 474, 530, 624, 943, 617, 865, 998, 481, 767, 48, 257, 168, 897, 502, 960, 747, 1023, 964, 374, 110, 680, 12, 55, 373, 27, 90, 166, 350, 489, 247, 722, 878, 390, 1010, 654, 559, 83, 250, 482, 382, 364, 409, 582, 328, 494, 518, 843, 778, 953, 563, 940, 914, 224, 188, 563, 260, 1021, 995, 747, 1009, 158, 446, 584, 754, 993, 433, 575, 653, 320, 968, 358, 1021, 513, 864, 654, 862, 96, 41, 490, 765, 214, 319, 168, 1019, 272, 713, 240, 136, 754, 527, 451, 143, 682, 277, 518, 265, 437, 360, 65, 519, 235, 365, 680, 575, 73, 167, 284, 936, 36, 135, 258, 109, 1000, 500, 978, 435, 978, 154, 640, 857, 368, 813, 783, 452, 822, 848, 190, 34, 25, 88, 869, 1019, 546, 836, 278, 14, 704, 651, 320, 65, 569, 921, 923, 54, 553, 616, 632, 2, 45, 553, 168, 414, 608, 629, 371, 819, 374, 143, 577, 532, 72, 29, 830, 820, 7, 90, 1014, 244, 472, 804, 471, 1007, 542, 395, 449, 694, 527, 87, 355, 855, 710, 480, 1009, 209, 76, 289, 119, 364, 636, 822, 611, 848, 700, 654, 578, 522, 612, 822, 255, 891, 306, 443, 122, 1016, 727, 525, 305, 109, 319, 375, 710, 206, 849, 871, 442, 927, 837, 818, 789, 912, 244, 549, 218, 934, 514, 139, 237, 901, 937, 764, 247, 524, 576, 988, 512, 99, 628, 180, 377, 472, 422, 204, 88, 607, 902, 475, 358, 824, 931, 230, 918, 655, 380, 330, 674, 258, 155, 716, 382, 30, 198, 353, 267, 240, 728, 64, 917, 96, 494, 266, 1022, 453, 4, 78, 426, 617, 206, 147, 11, 490, 387, 565, 333, 1, 606, 412, 940, 608, 733, 790, 1018, 759, 404, 1016, 68, 116, 454, 987, 799, 99, 581, 320, 246, 219, 813, 183, 43, 976, 859, 581, 941, 844, 365, 890, 531, 412, 876, 292, 122, 319, 4, 195, 602, 837, 812, 891, 426, 465, 137, 502, 761, 911, 63, 635, 504, 314, 1014, 258, 730, 533, 849, 581, 939, 413, 239, 181, 347, 7, 954, 17, 624, 545, 677, 458, 605, 266, 298, 163, 813, 347, 78, 305, 600, 561, 693, 588, 42, 879, 70, 507, 280, 751, 930, 237, 442, 792, 761, 724, 107, 325, 337, 900, 264, 161, 689, 445, 915, 430, 11, 244, 1000, 737, 730, 846, 531, 237, 657, 632, 1002, 473, 160, 279, 731, 645, 701, 983, 988, 345, 132, 82, 998, 752, 8, 556, 478, 1016, 224, 686, 468, 89, 81, 427, 246, 703, 511, 279, 398, 866, 980, 704, 295, 981, 229, 546, 740, 864, 704, 511, 548, 405, 593, 513, 42, 664, 931, 22, 225, 733, 734, 282, 381, 128, 893, 611, 895, 880, 238, 1022, 389, 828, 372, 575, 71, 657, 379, 549, 873, 283, 301, 693, 407, 174, 805, 251, 767, 513, 138, 698, 848, 223, 642, 686, 875, 963, 14, 82, 830, 693, 1001, 40, 105, 418, 883, 489, 50, 60, 874, 453, 423, 485, 800, 62, 464, 664, 732, 845, 369, 842, 124, 502, 368, 372, 375, 759, 248, 421, 285, 255, 818, 213, 447, 379, 146, 848, 832, 946, 188, 714, 775, 825, 739, 218, 139, 854, 337, 263, 713, 385, 198, 784, 334, 949, 78, 511, 84, 182, 266, 307, 927, 182, 282, 721, 605, 136, 374, 650, 475, 849, 904, 441, 222, 379, 665, 511, 506, 104, 661, 524, 322, 145, 218, 816, 225, 963, 148, 925, 776, 728, 341, 210, 453, 1009, 517, 596, 530, 849, 1009, 246, 202, 433, 254, 1024, 881, 552, 743, 16, 957, 443, 807, 385, 86, 681, 189, 695, 648, 277, 205, 23, 953, 140, 674, 507, 71, 613, 231, 614, 666, 838, 912, 891, 116, 447, 702, 845, 665, 775, 427, 917, 377, 751, 752, 955, 878, 513, 495, 496, 888, 607, 899, 548, 820, 778, 566, 163, 729, 71, 391, 876, 65, 277, 217, 241, 212, 699, 594, 970, 942, 413, 592, 673, 156, 623, 222, 112, 600, 773, 885, 383, 399, 163, 181, 654, 424, 622, 413, 290, 734, 626, 1023, 835, 292, 978, 255, 959, 667, 789, 507, 788, 742, 968, 206, 989, 799, 482, 359, 222, 1007, 621, 544, 416, 802, 938, 890, 60, 349, 340, 242, 121, 150, 531 };

	begin = clock();

	bitonicSequenceGenerator(0, 1023, vetor3);

	end = clock();

	double time_spent3 = (double)end - begin / CLOCKS_PER_SEC;

	int vetor4[1024] = { 673, 403, 633, 949, 723, 528, 208, 89, 648, 692, 565, 385, 10, 701, 618, 426, 639, 148, 978, 263, 713, 605, 649, 871, 686, 871, 536, 920, 1011, 926, 114, 9, 685, 319, 507, 292, 337, 904, 855, 438, 11, 434, 24, 617, 327, 608, 200, 96, 289, 363, 120, 786, 253, 362, 392, 904, 265, 644, 575, 9, 385, 993, 808, 147, 894, 162, 249, 138, 447, 66, 464, 785, 1007, 440, 474, 889, 0, 580, 180, 433, 141, 189, 668, 876, 587, 779, 859, 140, 12, 667, 861, 774, 505, 329, 730, 307, 595, 107, 628, 643, 76, 632, 492, 266, 12, 411, 548, 188, 420, 730, 911, 56, 811, 914, 749, 151, 886, 722, 210, 542, 263, 501, 386, 765, 285, 793, 712, 254, 169, 652, 327, 804, 792, 396, 865, 910, 887, 196, 124, 179, 500, 906, 567, 627, 819, 782, 572, 908, 614, 989, 374, 611, 108, 943, 111, 142, 827, 736, 105, 318, 856, 413, 123, 929, 349, 74, 148, 246, 751, 704, 811, 694, 925, 342, 60, 15, 914, 136, 268, 814, 808, 72, 22, 60, 92, 337, 86, 383, 651, 681, 725, 159, 122, 311, 478, 870, 617, 273, 309, 352, 528, 976, 486, 814, 90, 451, 389, 1017, 115, 3, 292, 49, 725, 628, 223, 877, 50, 275, 502, 618, 356, 226, 72, 903, 920, 119, 473, 272, 301, 347, 753, 149, 862, 497, 100, 340, 859, 559, 352, 966, 52, 65, 262, 828, 660, 99, 671, 976, 688, 129, 854, 603, 13, 693, 901, 731, 922, 990, 837, 758, 725, 107, 924, 92, 340, 982, 13, 384, 469, 909, 914, 655, 489, 390, 588, 544, 887, 96, 138, 794, 91, 421, 79, 992, 947, 35, 437, 542, 601, 537, 113, 958, 35, 819, 580, 669, 819, 113, 278, 819, 284, 338, 125, 786, 345, 574, 780, 996, 528, 446, 888, 301, 148, 1006, 584, 242, 304, 950, 112, 158, 767, 133, 645, 148, 563, 572, 147, 904, 768, 489, 469, 257, 847, 431, 231, 620, 244, 600, 87, 781, 927, 72, 799, 994, 109, 990, 614, 132, 881, 198, 172, 941, 324, 488, 57, 567, 798, 392, 303, 124, 581, 279, 768, 835, 1, 74, 631, 752, 44, 132, 798, 299, 517, 370, 1011, 38, 948, 347, 669, 290, 718, 495, 886, 638, 730, 30, 441, 775, 1006, 709, 524, 831, 817, 846, 590, 872, 892, 72, 811, 97, 185, 544, 961, 738, 891, 303, 927, 1022, 585, 43, 62, 891, 715, 430, 292, 1, 701, 722, 769, 881, 590, 697, 231, 823, 237, 472, 461, 329, 948, 200, 968, 660, 492, 519, 770, 964, 194, 583, 553, 708, 662, 661, 273, 14, 598, 815, 310, 149, 929, 510, 819, 280, 941, 123, 796, 277, 576, 726, 620, 101, 340, 410, 454, 758, 228, 418, 444, 929, 778, 110, 129, 763, 408, 133, 646, 484, 778, 463, 985, 765, 395, 961, 871, 80, 6, 429, 379, 418, 233, 171, 840, 543, 740, 726, 224, 866, 403, 693, 704, 169, 705, 900, 419, 803, 341, 735, 910, 846, 746, 365, 428, 360, 277, 386, 298, 645, 832, 718, 206, 722, 112, 199, 25, 110, 69, 691, 81, 501, 330, 449, 359, 1013, 382, 402, 907, 212, 229, 774, 303, 453, 569, 666, 48, 347, 168, 424, 178, 633, 263, 13, 478, 842, 26, 430, 894, 400, 107, 984, 980, 91, 765, 433, 901, 781, 187, 719, 329, 41, 859, 221, 593, 508, 460, 146, 1024, 685, 680, 386, 328, 411, 322, 113, 915, 338, 508, 773, 352, 87, 147, 823, 472, 240, 103, 407, 23, 230, 158, 93, 171, 94, 862, 874, 300, 380, 755, 314, 975, 920, 746, 773, 786, 348, 897, 488, 553, 881, 891, 247, 96, 972, 1006, 333, 392, 81, 774, 150, 342, 59, 318, 369, 688, 269, 732, 594, 495, 270, 949, 232, 963, 878, 311, 622, 334, 971, 203, 527, 365, 510, 89, 814, 1003, 486, 854, 383, 689, 724, 762, 329, 318, 803, 210, 895, 901, 640, 618, 747, 882, 731, 768, 1, 453, 468, 710, 281, 979, 506, 744, 82, 360, 946, 329, 488, 772, 56, 375, 1015, 240, 1017, 195, 163, 272, 33, 964, 385, 47, 239, 305, 73, 836, 718, 560, 812, 143, 608, 631, 1016, 594, 577, 188, 71, 939, 186, 216, 759, 888, 375, 568, 747, 201, 406, 157, 209, 444, 910, 871, 953, 686, 418, 306, 753, 838, 966, 720, 835, 859, 916, 448, 758, 129, 889, 298, 10, 641, 418, 387, 1015, 470, 382, 817, 341, 828, 870, 165, 866, 263, 414, 260, 473, 407, 537, 90, 248, 385, 711, 352, 98, 66, 737, 396, 498, 452, 109, 733, 414, 802, 304, 248, 122, 59, 416, 503, 85, 306, 961, 55, 963, 62, 544, 119, 159, 155, 449, 823, 205, 394, 513, 858, 285, 1, 714, 987, 107, 25, 263, 527, 732, 533, 879, 162, 491, 5, 909, 448, 315, 298, 246, 35, 788, 706, 333, 189, 924, 344, 387, 205, 319, 467, 64, 215, 930, 695, 618, 132, 96, 784, 799, 799, 495, 947, 986, 309, 21, 19, 155, 757, 726, 679, 418, 214, 588, 445, 389, 115, 259, 863, 363, 912, 668, 805, 555, 911, 272, 204, 855, 237, 556, 912, 156, 892, 960, 545, 173, 484, 931, 258, 108, 310, 892, 630, 1007, 195, 775, 824, 933, 765, 319, 288, 462, 194, 146, 314, 864, 152, 307, 791, 306, 802, 397, 355, 177, 306, 222, 41, 607, 419, 153, 18, 498, 1022, 223, 289, 370, 414, 415, 777, 981, 303, 52, 347, 338, 63, 393, 170, 410, 577, 586, 613, 761, 269, 735, 356, 73, 810, 518, 819, 105, 412, 951, 118, 664, 113, 428, 994, 531, 274, 707, 340, 84, 663, 305, 534, 788, 278, 759, 178, 349, 247, 998, 732, 818, 655, 288, 720, 89, 538, 375, 582, 338, 120, 38, 491, 712, 173, 917, 225, 381, 364, 943, 608, 441, 62, 347, 607, 704, 355, 233, 631, 866, 564, 594, 460, 541, 97, 244, 166, 211, 563, 924, 11, 455, 409, 509, 610, 1007, 192, 575, 430, 619, 109, 537, 757, 336, 343, 256, 576, 258, 121, 201, 422, 613, 208, 305, 130, 610};

	begin = clock();

	bitonicSequenceGenerator(0, 1023, vetor4);

	end = clock();

	double time_spent4 = (double)end - begin / CLOCKS_PER_SEC;

	int vetor5[1024] = { 949, 28, 655, 832, 843, 601, 354, 234, 282, 120, 323, 496, 263, 371, 600, 990, 709, 350, 394, 384, 207, 319, 78, 940, 512, 160, 173, 224, 139, 527, 657, 394, 371, 502, 253, 952, 896, 40, 479, 544, 684, 916, 666, 565, 91, 824, 310, 464, 357, 778, 231, 976, 952, 636, 597, 591, 74, 151, 132, 735, 241, 306, 823, 732, 894, 978, 838, 3, 1004, 417, 949, 278, 190, 52, 402, 635, 111, 830, 225, 29, 66, 450, 668, 733, 614, 198, 227, 823, 157, 191, 1020, 482, 910, 341, 399, 25, 534, 340, 574, 335, 833, 629, 299, 36, 777, 973, 226, 252, 299, 950, 284, 61, 794, 909, 753, 471, 618, 515, 1017, 293, 766, 433, 834, 637, 115, 76, 422, 353, 118, 984, 396, 268, 565, 495, 500, 937, 824, 590, 363, 142, 618, 21, 953, 130, 39, 30, 945, 346, 500, 31, 967, 568, 527, 155, 964, 338, 464, 591, 318, 45, 142, 1005, 980, 711, 248, 327, 774, 12, 972, 828, 739, 211, 607, 271, 43, 706, 963, 790, 809, 891, 87, 858, 388, 970, 294, 130, 876, 149, 378, 720, 28, 600, 322, 277, 85, 27, 362, 210, 750, 484, 476, 712, 438, 663, 15, 988, 152, 149, 176, 229, 776, 207, 437, 870, 151, 400, 472, 927, 49, 263, 432, 296, 61, 323, 978, 590, 838, 74, 992, 902, 189, 136, 638, 358, 503, 730, 287, 827, 18, 829, 618, 448, 649, 233, 872, 688, 794, 600, 74, 903, 495, 80, 929, 431, 334, 643, 393, 116, 616, 791, 799, 461, 239, 803, 331, 190, 570, 872, 169, 315, 907, 334, 452, 429, 658, 509, 344, 589, 805, 300, 289, 550, 467, 97, 563, 24, 309, 662, 975, 106, 702, 641, 64, 121, 582, 555, 161, 1000, 118, 431, 12, 876, 930, 781, 104, 234, 746, 974, 40, 122, 983, 229, 181, 333, 855, 234, 68, 281, 668, 368, 69, 529, 198, 95, 284, 515, 900, 183, 363, 810, 222, 536, 797, 172, 47, 878, 692, 209, 655, 324, 85, 184, 437, 929, 105, 40, 419, 709, 832, 678, 348, 522, 468, 534, 531, 936, 33, 954, 392, 901, 397, 437, 265, 743, 643, 41, 565, 211, 275, 55, 636, 444, 607, 763, 640, 10, 159, 175, 155, 367, 108, 785, 302, 110, 509, 414, 868, 135, 731, 673, 726, 326, 894, 477, 10, 648, 1015, 26, 350, 667, 747, 287, 108, 168, 507, 1015, 977, 400, 489, 588, 818, 604, 46, 215, 186, 871, 223, 648, 925, 497, 972, 524, 120, 590, 327, 815, 826, 431, 533, 724, 198, 498, 945, 538, 8, 498, 1004, 966, 380, 143, 471, 342, 697, 716, 550, 416, 305, 879, 407, 265, 850, 756, 771, 324, 125, 63, 524, 151, 22, 310, 700, 134, 366, 9, 53, 20, 835, 494, 441, 696, 35, 31, 289, 750, 612, 692, 519, 1016, 786, 656, 105, 464, 768, 988, 465, 218, 149, 557, 423, 906, 326, 873, 552, 783, 544, 463, 512, 644, 745, 974, 794, 72, 680, 704, 180, 577, 816, 594, 120, 372, 94, 951, 195, 4, 18, 794, 615, 940, 769, 216, 163, 946, 987, 600, 1009, 802, 78, 291, 336, 449, 652, 22, 515, 608, 984, 391, 356, 857, 226, 96, 275, 719, 809, 48, 47, 945, 542, 550, 1018, 972, 187, 121, 803, 811, 342, 22, 874, 345, 314, 94, 462, 687, 380, 237, 74, 930, 758, 943, 418, 785, 261, 973, 411, 41, 770, 309, 227, 710, 738, 931, 207, 164, 927, 692, 240, 565, 383, 449, 88, 458, 724, 81, 816, 472, 787, 378, 334, 559, 889, 1016, 11, 833, 711, 179, 40, 45, 57, 502, 770, 852, 947, 399, 351, 278, 52, 1023, 54, 251, 176, 525, 264, 402, 910, 657, 932, 37, 795, 1016, 570, 378, 715, 294, 801, 694, 84, 249, 916, 241, 888, 12, 739, 810, 582, 199, 72, 28, 762, 396, 459, 243, 647, 1012, 527, 951, 161, 540, 298, 562, 416, 914, 371, 967, 233, 224, 947, 283, 630, 916, 929, 653, 730, 561, 42, 416, 633, 9, 329, 428, 3, 42, 713, 925, 381, 847, 252, 585, 452, 833, 713, 447, 289, 480, 820, 802, 143, 140, 348, 784, 824, 615, 79, 72, 443, 272, 76, 676, 1015, 637, 782, 602, 403, 573, 602, 257, 658, 404, 369, 242, 756, 388, 630, 412, 341, 290, 808, 137, 749, 818, 345, 761, 591, 539, 519, 241, 56, 210, 698, 75, 882, 510, 74, 170, 411, 236, 670, 153, 86, 132, 189, 393, 172, 668, 117, 152, 671, 14, 652, 42, 799, 236, 828, 1004, 256, 628, 633, 280, 200, 194, 933, 877, 759, 493, 496, 348, 249, 95, 398, 171, 230, 377, 425, 866, 101, 685, 254, 169, 227, 377, 809, 578, 68, 686, 182, 583, 299, 486, 695, 806, 119, 305, 455, 249, 512, 753, 1021, 262, 721, 85, 25, 662, 428, 295, 497, 183, 3, 570, 633, 322, 663, 240, 490, 205, 449, 636, 766, 527, 362, 907, 646, 139, 231, 1024, 236, 270, 159, 635, 715, 612, 707, 898, 373, 234, 582, 442, 299, 378, 805, 39, 337, 417, 656, 928, 133, 831, 516, 1001, 91, 294, 878, 445, 97, 60, 280, 732, 770, 941, 977, 395, 159, 921, 333, 334, 592, 325, 309, 350, 425, 1003, 659, 879, 625, 410, 319, 820, 697, 613, 900, 223, 734, 53, 997, 693, 774, 734, 135, 914, 471, 352, 552, 770, 545, 363, 901, 715, 199, 102, 961, 702, 853, 449, 764, 646, 832, 664, 653, 817, 165, 376, 97, 292, 169, 858, 901, 245, 81, 682, 796, 708, 1016, 947, 661, 96, 588, 318, 948, 444, 480, 387, 890, 861, 26, 793, 344, 752, 378, 127, 821, 483, 522, 365, 585, 691, 347, 140, 918, 312, 129, 157, 865, 964, 697, 729, 364, 776, 489, 876, 960, 1012, 885, 891, 620, 665, 618, 182, 425, 1011, 983, 618, 665, 832, 754, 735, 266, 706, 988, 674, 937, 512, 925, 910, 936, 89, 1005, 412, 1006, 262, 116, 550, 264, 955, 1024, 797, 1011, 34, 346, 205, 953, 68, 264, 265, 145, 246, 64, 192, 29, 856, 713, 74, 623, 85, 498, 495, 313, 978};

	begin = clock();

	bitonicSequenceGenerator(0, 1023, vetor5);

	end = clock();

	double time_spent5 = (double)end - begin / CLOCKS_PER_SEC;
	
	for (int i = 0; i < 1024; i++)
	{
		printf("|%d|", vetor[i]);
	}

	char a[10];
	printf("\n");
	printf("TIME SPENT 1");
	printf("\n %f", time_spent1);

	printf("\n TIME SPENT 2");
	printf(" \n %f", time_spent2);

	printf("\n TIME SPENT 3");
	printf("\n %f", time_spent3);

	printf("\n TIME SPENT 4");
	printf("\n %f", time_spent4);

	printf("\n TIME SPENT 5");
	printf("\n %f", time_spent5);

	printf("\n AVERAGE");
	printf("\n %f", (time_spent1 + time_spent2 + time_spent3 + time_spent4 + time_spent5) / 5);
	scanf_s("%s", a);

}