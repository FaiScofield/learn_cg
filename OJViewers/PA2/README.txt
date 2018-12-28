ConvexHullViewer.exe 凸包可视化效果查看器
==========================================
主要功能：
Open Points：导入点集，其中点集的格式要求与OJ的输入格式要求一致
Open Convex Hull：导入凸包，其中凸包表示为一系列极点的标号，从0开始，每个标号占据一行
Show Convex Hull：显示凸包选项
Show PointID：显示凸包上的点的标号
Reset View：重新缩放视角

除此之外，可直接在窗体中拖动或者滚轮缩放界面。
Open Points与Open Convex Hull对应的示例文件是example/ch_points.txt和example/ch_convex_hull.txt

IntersectionViewer.exe 求交可视化效果查看器
==========================================
主要功能：
Open Scene：导入交通地图，其格式与OJ上的输入格式要求一致
Open Intersection：导入交点，交点以空格分隔的x，y坐标表示，每个交点占据一行
Show Intersection：显示交点
Show Label：显示交点上的标号
Reset View：重新缩放视角

除此之外，可直接在窗体中拖动或者滚轮缩放界面。
Open Scene与Open Intersection对应的示例文件是example/gi_scene.txt与gi_intersection.txt

RoomViewer.exe 简单多边形内最短路径可视化效果查看器
==========================================
主要功能：
Open Room Map：导入房间地图，其格式与OJ上的输入格式要求一致
Open Path：导入路径，其格式与OJ上的输出格式要求一致
Show Path：显示路径
Show CornerID：显示表示房间的多边形顶点标号
Reset View：重新缩放视角

除此之外，可直接在窗体中拖动或者滚轮缩放界面。
Open Room Map与Open Path对应的示例文件是example/tri_room.txt与tri_path.txt

PartyViewer.exe 平面上最近点可视化效果查看器
==========================================
主要功能：
Open Party：导入舞会地图，其格式与OJ上的输入格式要求一致
Open Pairs：导入为每个女孩寻找的配对男孩，其格式与OJ上的输出格式要求一致
Show Pairs：显示配对情况
Show PersonID：显示表示房间的多边形顶点标号
Reset View：重新缩放视角

除此之外，可直接在窗体中拖动或者滚轮缩放界面。
Open Party与Open Pairs对应的示例文件是example/vd_party.txt与vd_pairs.txt

================
以上程序均基于MFC，请确保程序exe与附带的dll文件在同一个目录下方可正常运行
