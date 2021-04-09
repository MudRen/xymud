#include <ansi.h>
inherit VRM_SERVER;

void create()
{
        set_maze_map_color(HIW);
        set_inherit_room("/d/maze/tupo40-2/room");
        set_npcs_rate(90);
        set_display_map(2);     
        //迷宫的单边长
        set_maze_long(6);
        //每个房间的出口，默认是2
        set_maze_exit(2);
        //无出口的方向不显示，默认是显示
        set_maze_exittype(1);
        //入口方向(出口在对面)
        set_entry_dir("west");
        //入口与区域的连接方向
        set_link_entry_dir("west");

        //入口与区域的连接档案名
        set_link_entry_room(__DIR__"enter");

        //出口与区域的连接方向
        set_link_exit_dir("north");

        //出口与区域的连接档案名
        set_link_exit_room(__DIR__"out");  

         //普通房间描述
        set_maze_room_short("大森林");
        set_maze_room_desc(@LONG
到处郁郁葱葱，千万片绿叶从枝头婉转曼妙的飘落而下，原本别具风情的森林，在转眼间变得凄迷如梦，千万片绿叶交织落索，一场绿雨在林中渐渐弥漫，直到遮掩住空气，遮掩住视线，遮掩住呼吸。
    无数长藤与并不算粗大的树木纠缠成浓浓的一团。就那么乱七八糟的生长着。   
LONG); 
        //入口房间短描述 
        set_entry_short("建木遗迹入口"); 
        //入口房间描述 
        set_entry_desc(@LONG
到处郁郁葱葱，无数长藤与并不算粗大的树木纠缠成浓浓的一团。就那么乱七八糟的生长着。
LONG);
        //出口房间短描述 
        set_exit_short("大森林"); 
        //出口房间描述 
        set_exit_desc(@LONG
到处郁郁葱葱，千万片绿叶从枝头婉转曼妙的飘落而下，原本别具风情的森林，在转眼间变得凄迷如梦，千万片绿叶交织落索，一场绿雨在林中渐渐弥漫，直到遮掩住空气，遮掩住视线，遮掩住呼吸。
    无数长藤与并不算粗大的树木纠缠成浓浓的一团。就那么乱七八糟的生长着。
LONG);
        // 迷宫房间是否为户外房间？ 
        set_outdoors(0);                                                

        //迷宫房间是否刷新且刷新时间设置
        set_maze_refresh(10800);
        //迷宫销毁时间
        set_remove_time(10800);
}

