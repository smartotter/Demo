void GB15(int x,int y,int *NAME);


/*=========================================================================*/

 int *UNITNAME;

/*背景地图 墙*/
int MAP[30][30]={
                 3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,
                 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
                 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
                 2,0,0,3,1,1,1,1,1,1,1,1,1,1,8,0,0,0,8,1,1,1,1,1,1,1,4,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,10,1,1,1,1,1,1,1,1,1,1,9,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,5,1,1,1,1,1,1,1,9,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,10,1,1,1,1,1,1,0,0,1,1,6,0,0,0,3,1,1,1,1,1,1,1,9,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,
                 2,0,0,5,1,1,1,0,0,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,1,6,0,0,2,
                 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
                 2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
                 5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6,


                };



/*前景地图 人物*/
int MAP2[30][30]={
                 -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                 -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,
                 -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,
                 -1,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,-1,-1,-1,-1,-1,-1,0,0,-1,-1,-1,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,-1,0,0,-1,
                 -1,0,0,-1,-1,-1,-1,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,-1,
                 -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,
                 -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,


                };






/*=========================================================================*/

/*地图元素*/

 int UNIT_00[15][15]={
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                     };


 int UNIT_01[15][15]={
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                     };


 int UNIT_02[15][15]={
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                     };


 int UNIT_03[15][15]={
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,8,8,8,8,8,8,8,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                     };


 int UNIT_04[15][15]={
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                     };


 int UNIT_05[15][15]={
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,8,8,8,8,8,8,8,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                     };


 int UNIT_06[15][15]={
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                     };


 int UNIT_07[15][15]={
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                     };



 int UNIT_08[15][15]={
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                     };



 int UNIT_09[15][15]={
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                     };




 int UNIT_10[15][15]={
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,8,8,8,8,8,8,8,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,
                     };








/*=========================================================================*/




void GB15(int x,int y,int *NAME)                             /*绘制地图元素*/
{ int i,j,X,Y;


  X=x;
  Y=y;
 for(i=0,y=Y;i<=14;i++,y++)
    {
     for(j=0,x=X;j<=14;j++,x++)
     if(*(NAME+(i*15+j))==0){;}
     else{putpixel(x,y,*(NAME+(i*15+j)));}
    }


}






