SimplePolygonViewer.exe 多边形和三角剖分可视化效果查看器
==========================================
主要功能：
Open Polygon/Points：导入点集，其中点集的格式要求与OJ的输入格式要求一致
Open Mesh: 导入三角网格，其中三角网格的格式参见示例文件。每一行表示一个三角形，每个三角形由三个点的标号表示，其中标号从0开始
Show Point IDs：显示点集标号
Show Mesh: 显示三角网格
Reset View：重新缩放视角

除此之外，可直接在窗体中拖动或者滚轮缩放界面。
Open Polygon/Points与Open Mesh对应的示例文件是example/points.txt和example/delaunay_triangulation.txt

WallsViewer.exe RayShooting问题可视化效果查看器
=========================================
主要功能：
Open Segments and Queries: 导入线段已经待查询的点集，其格式与OJ的输入格式要求一致
Open Results: 导入查询结果，其格式与OJ的输出格式要求一致
Show Results: 显示查询结果
Reset View：重新缩放视角

除此之外，可直接在窗体中拖动或者滚轮缩放界面。
Open Segments and Queries与Open Results对应的示例文件是example/walls_queries.txt和example/query_results.txt

================
以上程序均基于MFC，请确保程序exe与附带的dll文件在同一个目录下方可正常运行
