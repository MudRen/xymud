#include <ansi.h>
#include <combat.h>
inherit SSERVER;

mapping query_shentong(object who)
{
	string st,wx,wx_type,name,*names;
	int wx_lvl;
	if( !who || who->query_level()<40 )
		return 0;
	if( !stringp(st=who->query("shentong/40")) )
		return 0;
	if( sscanf(st,"%s_%s_%d",wx,wx_type,wx_lvl)!=3 )
		return 0;
	switch(wx)
	{
		case "金" : 
			if( wx_type=="阴" )
				names = ({ "神剑","剑无量","突剑四方","乱刃狂舞","五狱华斩","日月轮斩","天地无用", });
			else	names = ({ "鬼戟","飞鬼戟","八门金锁","三日月斩","三圣华斩","神剑闪华","天地无用", });
			break;
		case "木" :
			if( wx_type=="阴" )
				names = ({ "花香","苍木气","百花绕","太乙青","雷光振杀","旋龙天舞","天雷殛电",});
			else	names = ({ "妖盾","雷击闪","浮雷阵","雷光波动","雷光焦狱","奔雷袭电","天雷殛电", });
			break;
		case "水" :
			if( wx_type=="阴" )
				names = ({ "地泉","莲华","命疗术","鬼面盾","莲华落","地泉鲸浪","冰风刃舞",});
			else	names = ({ "旋灯","冰柱刺","莲华爆","水月斩","双月斩","冰柱群峰","冰风刃舞",});
			break;
		case "火" :
			if( wx_type=="阴" )
				names = ({ "火雷","旋龙","八面火","炎流星","旋灯剑","虎咆阳炎","火雷星雨",});
			else	names = ({ "伏焰","炎墙","集火柱","天火焚","炎龙无双","烈火旋灯","火雷星雨",});
			break;
		case "土" :
			if( wx_type=="阴" )
				names = ({ "炬石","绝命坝","地茅刺","炬石轰","震地诀","箭石雨","大地狂啸",});
			else	names = ({ "滚石","突石剑","突袭石","箭石坠","裂地刃","地泉列劲","大地狂啸",});
			break;
		default : return 0;
	}	
	if( wx_lvl>sizeof(names) )
		wx_lvl = sizeof(names);
	name = names[wx_lvl-1];
	return ([
		"name" : name,
		"wx"   : wx,
		"lvl"  : wx_lvl,
		"type" : wx_type,
	]);					
}

string query_shentong_file(object who)
{
	mapping data;
	string dir = __DIR__"40/";
	if( !who || who->query_level()<40 )
		return 0;
	if( !mapp(data=query_shentong(who)) 
	 || sizeof(data)<1 )
		return 0;
	return sprintf("%s%s/%s/%d",dir,data["wx"],data["type"],data["lvl"]);		
}

int cast(object me, object target)
{	
	string file;
	if( me->query_level()<40 )
		return notify_fail("你的人物等级不够。\n");
return notify_fail("近期开放。\n");
	notify_fail("你还没有自己的专属小神通。\n");
	if( !stringp(file=query_shentong_file(me)) )
		return 0;
	return file->cast(me,target);			
}

int help(object me)
{
	string file;
	if( me->query_level()<40 
	 || !stringp(file=query_shentong_file(me)) )
	{
		write(@HELP
        神通名称：小神通
        神通条件：
                  人物等级40级
                  通过五行副本筑基
HELP);
		return 1;		
	}
	else return file->help(me);
}
