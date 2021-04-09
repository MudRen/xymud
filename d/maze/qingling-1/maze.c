
#include <ansi.h>
inherit VRM_SERVER;

void create()
{
        set_maze_map_color(HIW);
        set_inherit_room("/d/maze/qingling-1/room");
        set_npcs_rate(90);
        set_display_map(2);     
        //迷宫的单边长
        set_maze_long(7);
        //每个房间的出口，默认是2
        set_maze_exit(3);
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
        set_maze_room_short( ({HIR,HIC,HIB,HIM,HIY,HIW,})[random(6)]+"兵马俑阵"NOR );
        set_maze_room_desc(@LONG
你来到一个巨大的兵马俑阵中，天高云阔，成千上万个栩栩如生的兵马俑排列成几
十路纵队，仿佛正在从四面八方呼啸而来，你不禁被这个宏伟的场面惊倒。

LONG); 
        //入口房间短描述 
        set_entry_short("始皇陵"); 
        //入口房间描述 
        set_entry_desc(@LONG
这是座落在官道以东的一个大丘陵，呈覆斗型。站在丘陵上极目远眺，不禁心旷神
怡。旁边有一座高大的石碑：
LONG);
        //出口房间短描述 
        set_exit_short("始皇陵二层入口"); 
        //出口房间描述 
        set_exit_desc(@LONG
你来到一个巨大的兵马俑阵中，天高云阔，成千上万个栩栩如生的兵马俑排列成几
十路纵队，仿佛正在从四面八方呼啸而来，你不禁被这个宏伟的场面惊倒。
    再往北走便是始皇陵二层入口。
LONG);
        // 迷宫房间是否为户外房间？ 
        set_outdoors(0);                                                

        //迷宫房间是否刷新且刷新时间设置
        set_maze_refresh(10800);
        //迷宫销毁时间
        set_remove_time(10800);
}

