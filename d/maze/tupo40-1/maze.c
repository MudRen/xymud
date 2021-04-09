/*
金	蜀山	川中蜀道
头衔	五行	金	五行	获得神通(阴)	获得神通（阳）
玄溟	辛	死士	辛	神剑	鬼戟
幽谷	庚	鬼卒	酉	剑无量	飞鬼戟
困守	酉	鬼兵	庚	突剑四方	八门金锁
破阵	申	苗巫祭祀	辛	乱刃狂舞	三日月斩
蜀州	--	东夷众	酉	五狱华斩	三圣华斩
		蛮巨人	申	日月轮斩	神剑闪华
		巴蛇	---	天地无用	天地无用
金行至戾，木行至生，水行至柔，火行至烈，土行至厚		
*/
#include <ansi.h>
inherit VRM_SERVER;

void create()
{
        set_maze_map_color(HIW);
        set_inherit_room("/d/maze/tupo40-1/room");
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
        set_maze_room_short("销金窝");
        set_maze_room_desc(@LONG
一片毫无生气地广漠空地，越向深处走，巨石和树木颜色也就越像金属。形状也越来越犀利。
渐渐地在石头上都出现了劲锐地锋刃。树木也是上窄下粗。好像一根根指天地长梭。
    突然从远处传来一阵好像万剑交击，金龙腾挪、无数铃铛一起震动地金属震鸣声，
一时间在山峦间栖息的鸟群尽数被惊起，远远望去就像一片铺天盖地的黑云，在山峰
之间辗转奔腾，说不出的壮观！   
LONG); 
        //入口房间短描述 
        set_entry_short("古蜀道口"); 
        //入口房间描述 
        set_entry_desc(@LONG
蜀道难，难于上青天，走惯平坦大道的你今天才深深体会到行路的艰难，前面一条
歪歪斜斜，松松垮垮的木栈道，断断续续的通往山顶。
LONG);
        //出口房间短描述 
        set_exit_short("销金窝"); 
        //出口房间描述 
        set_exit_desc(@LONG
一片毫无生气地广漠空地，越向深处走，巨石和树木颜色也就越像金属。形状也越来越犀利。
渐渐地在石头上都出现了劲锐地锋刃。树木也是上窄下粗。好像一根根指天地长梭。
    突然从远处传来一阵好像万剑交击，金龙腾挪、无数铃铛一起震动地金属震鸣声，
一时间在山峦间栖息的鸟群尽数被惊起，远远望去就像一片铺天盖地的黑云，在山峰
之间辗转奔腾，说不出的壮观！  
LONG);
        // 迷宫房间是否为户外房间？ 
        set_outdoors(0);                                                

        //迷宫房间是否刷新且刷新时间设置
        set_maze_refresh(10800);
        //迷宫销毁时间
        set_remove_time(10800);
}

