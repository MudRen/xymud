#include <ansi.h>
inherit VRM_SERVER;

void create()
{
        set_maze_map_color(HIW);
        set_inherit_room("/d/maze/tupo40-5/room");
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
        set_maze_room_short("终南幽谷");
        set_maze_room_desc(@LONG
这里是终南山中一处罕见之处。植被到了这里便渐渐稀少起来。放眼望去，尽是苍黄土色。
空气中流连着肉眼可见的土色之气，你走了片刻，便染了一身的泥巴，变成了土人。
   
LONG); 
        //入口房间短描述 
        set_entry_short("终南山"); 
        //入口房间描述 
        set_entry_desc(@LONG
终南山又称太乙山，距长安城八十多里，素有“锦秀巨屏拱长安”之说。据传老子
曾在山中讲经。这条大官道穿越终南山口，两面秀峰入云，却无明显之路可以上山。
    山中有一奇妙之处，乃是东土大唐土极之地。

LONG);
        //出口房间短描述 
        set_exit_short("幽谷深处"); 
        //出口房间描述 
        set_exit_desc(@LONG
快到幽谷至深之处了，来到这里仿若进入了一个苍黄的世界。此地植被差不多了无踪迹，放眼望去，除了土还是土。
    空气中流连着肉眼可见的土色之气，你站立片刻，便染了一身的泥巴色，变成了土人。
    
LONG);
        // 迷宫房间是否为户外房间？ 
        set_outdoors(0);                                                

        //迷宫房间是否刷新且刷新时间设置
        set_maze_refresh(10800);
        //迷宫销毁时间
        set_remove_time(10800);
}

