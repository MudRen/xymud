#include <ansi.h>
inherit VRM_SERVER;

void create()
{
        set_maze_map_color(HIW);
        set_inherit_room("/d/maze/tupo40-4/room");
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
        set_maze_room_short("星石巨坑");
        set_maze_room_desc(@LONG
身处一个巨大的坑道之中，方圆数里。四野一片红黄色的荒凉，到处
是烤得发红的碎石和砂土。
   
LONG); 
        //入口房间短描述 
        set_entry_short("坑旁"); 
        //入口房间描述 
        set_entry_desc(@LONG
眼前是一个一望无边的大土坑，据说乃是天上陨星落下所致。四下里寸草不生，一片红黄色的荒凉，到处
是烤得发红的碎石和砂土。
    你待了片刻便不由汗如雨下。

LONG);
        //出口房间短描述 
        set_exit_short("星石坑"); 
        //出口房间描述 
        set_exit_desc(@LONG
身处一个巨大的坑道之中，方圆数里。四野一片红黄色的荒凉，到处
是烤得发红的碎石和砂土。

LONG);
        // 迷宫房间是否为户外房间？ 
        set_outdoors(0);                                                

        //迷宫房间是否刷新且刷新时间设置
        set_maze_refresh(10800);
        //迷宫销毁时间
        set_remove_time(10800);
}

