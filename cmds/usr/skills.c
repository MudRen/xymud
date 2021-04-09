// skills.c
#include <ansi.h>
inherit F_CLEAN_UP;

string *skill_level_desc = ({
                HIB "初学乍练" NOR,HIB "不知所以" NOR,HIB "粗通皮毛" NOR,
                HIB "略识之无" NOR,HIB "渐有所悟" NOR,YEL "半生不熟" NOR,
                YEL "马马虎虎" NOR,YEL "平淡无奇" NOR,YEL "平平常常" NOR,
                YEL "触类旁通" NOR,HIY "略有小成" NOR,HIY "已有小成" NOR,
                HIY "心领神会" NOR,HIY "深入浅出" NOR,HIY "略有大成" NOR,
                MAG "已有大成" NOR,MAG "挥洒自如" NOR,MAG "驾轻就熟" NOR,
                MAG "出类拔萃" NOR,MAG "初入佳境" NOR,RED "神乎其技" NOR,
                RED "威不可当" NOR,RED "出神入化" NOR,RED "豁然贯通" NOR,
                RED "超群绝伦" NOR,HIR "登峰造极" NOR,HIR "无可匹敌" NOR,
                HIR "卓然大家" NOR,HIR "一代宗师" NOR,HIR "神功盖世" NOR,
                HIC "举世无双" NOR,HIC "惊世骇俗" NOR,HIC "独步天下" NOR,
                HIC "空前绝后" NOR,HIC "旷古绝伦" NOR,HIG "登堂入室" NOR,
                HIG "超凡入圣" NOR,HIG "震古铄今" NOR,HIG "深藏不露" NOR,
                HIG "返璞归真" NOR,HIW "深不可测" NOR
	});

string *knowledge_level_desc = ({
		BLU "新学乍用" NOR,BLU "不甚了了" NOR,BLU "不知端倪" NOR,
		HIB "平淡无奇" NOR,HIB "司空见惯" NOR,HIB "初窥门径" NOR,
		YEL "略知一二" NOR,YEL "茅塞顿开" NOR,YEL "略识之无" NOR,
		HIY "滚瓜烂熟" NOR,HIY "马马虎虎" NOR,HIY "轻车熟路" NOR,
		HIM "运用自如" NOR,HIM "触类旁通" NOR,HIM "深入浅出" NOR,
		HIR "已有小成" NOR,HIR "心领神会" NOR,HIR "了然于胸" NOR,
		MAG "见多识广" NOR,MAG "无所不通" NOR,MAG "卓尔不群" NOR,
		CYN "满腹经纶" NOR,CYN "豁然贯通" NOR,CYN "博古通今" NOR,
		HIC "博大精深" NOR,HIC "超群绝伦" NOR,HIC "举世无双" NOR,
		WHT "独步天下" NOR,WHT "震古铄今" NOR,WHT "超凡入圣" NOR,
		HIW "深不可测" NOR
});

string *shentong_level_desc = ({
		BLU "初窥神通" NOR,BLU "神通初具" NOR,BLU "粗通神通" NOR,
		HIB "可有可无" NOR,HIB "神通渐悟" NOR,HIB "小试神通" NOR,
		YEL "略晓神通" NOR,YEL "神通小悟" NOR,YEL "小成神通" NOR,
		HIY "神通娴熟" NOR,HIY "如指臂使" NOR,HIY "车到山前" NOR,
		HIM "如意神通" NOR,HIM "触类旁通" NOR,HIM "神通熟识" NOR,
		CYN "神通大成" NOR,CYN "豁然贯通" NOR,CYN "博古通今" NOR,
		HIC "博大精深" NOR,HIC "超群绝伦" NOR,HIC "举世无双" NOR,
		WHT "独步天下" NOR,WHT "震古铄今" NOR,WHT "超凡入圣" NOR,
		HIW "深不可测" NOR
});

string skill_level(string, int);

string ob_query_skill(object ob,string skill,string color)
{
	int x,y,z;
	string str;
	x = ob->query_skill(skill,1);
	y = ob->query_skill(skill,2);
	z = x-y;
	if( color!=NOR )
		str = sprintf(color+"%13d"+color,x);
	else
	{	
		if( z>0 )
			str = sprintf(HIR"%13d"NOR,x);
		else	str = sprintf(NOR"%13d"NOR,y);
	}	
	return str;	
}

string who_query_skill(object who)
{
	string *base,arg,*mapped,*sname,color;
	mapping skl,lrn,mp;
	string *my_base,*my_st,*my_know,*my_other,skill,str,level;
	int i,start;
	
	if( !who )
		return "";
	base = ({
		"unarmed","sword","blade","art","dagger",
		"stick","staff","throwing","force","parry",
		"dodge","spells","zhenfa","whip","spear",
		"axe","mace","fork","rake","archery",
		"hammer",
	});	
	arg = "";
	skl = who->query_skills();
	mp = who->query_skill_map();
	if( mp && mapp(mp) ) 
		mapped = values(mp);
	else	mapped = ({});
	lrn = who->query_learned();
	if( !lrn || !mapp(lrn) ) 
		lrn = ([]);
	sname  = sort_array( keys(skl), (: strcmp :) );
	my_base = my_st = my_know = my_other = ({});
	for(i=0; i<sizeof(sname); i++)
	{
		skill = sname[i];
		if( member_array(skill,base)!=-1 )
			my_base+= ({skill});
		else if( SKILL_D(skill)->type() == "knowledge" )
			my_know+= ({skill});
		else if( SKILL_D(skill)->type() == "shentong" )
			my_st+= ({skill});
		else	my_other+= ({skill});	 		 	
	}
	if( sizeof(my_base)>=1 )
		start = 1;
	else if( sizeof(my_know)>=1 )
		start = 2;
	else if( sizeof(my_other)>=1 )
		start = 3;
	else	start = 4;				
	
	switch(start)
	{
		case 1 : arg+= GRNBLU"┏"NOR HIC" 基本技能 "NOR GRNBLU"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"NOR"\n";break;
		case 2 : arg+= GRNBLU"┏"NOR HIG" 生活技能 "NOR GRNBLU"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"NOR"\n";break;
		case 4 : arg+= GRNBLU"┏"NOR HIW" 神通技能 "NOR GRNBLU"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"NOR"\n";break;
		default: arg+= GRNBLU"┏"NOR HIR" 特殊技能 "NOR GRNBLU"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"NOR"\n";break; 
	}
	if( sizeof(my_base)>=1 )
	{
		sname  = sort_array( my_base, (: strcmp :) );
		for(i=0; i<sizeof(sname); i++)
		{
			skill = sname[i];
			level = SKILL_D(skill)->level_description(skl[skill]);
			if( !level || !stringp(level) )
				level = skill_level("base", skl[skill]);
			if( lrn[skill] >= ((skl[skill]+1) * 10) )
				color = HIM;
			else	color = NOR;
			if( color!=NOR )
				level = COLOR_D->replace_color(color+COLOR_D->clean_color(level),1);			
			arg+= sprintf("%-2s%2s%-30s%-10s%13s/%13-d%s\n",
					(lrn[skill] >= ((skl[skill]+1) * 10) ) ? GRNBLU"┃"NOR HIM+" " : GRNBLU"┃"NOR+" ",
					"  "+color,
					to_chinese(skill) + " (" + skill + ")",
            				level,
            				ob_query_skill(who,skill,color),
            				(int)lrn[skill],
					GRNBLU"┃"NOR,);
		}	
	}
	if( sizeof(my_know)>=1 )
	{
		if( start!=2 )
			arg+= GRNBLU"┣"NOR HIG" 生活技能 "NOR "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"GRNBLU"┫"NOR"\n";
		sname  = sort_array( my_know, (: strcmp :) );
		for(i=0; i<sizeof(sname); i++)
		{
			skill = sname[i];
			level = SKILL_D(skill)->level_description(skl[skill]);
			if( !level || !stringp(level) )
				level = skill_level("knowledge", skl[skill]);
			if( lrn[skill] >= ((skl[skill]+1) * 10) )
				color = HIM;
			else	color = NOR;	
			if( color!=NOR )
				level = COLOR_D->replace_color(color+COLOR_D->clean_color(level),1);		
			arg+= sprintf("%-2s%2s%-30s%-10s%13s/%13-d%s\n",
					(lrn[skill] >= ((skl[skill]+1) * 10) ) ? GRNBLU"┃"NOR HIM+" " : GRNBLU"┃"NOR+" ",
					"  "+color,
					to_chinese(skill) + " (" + skill + ")",
            				level,
            				ob_query_skill(who,skill,color),
            				(int)lrn[skill],
					GRNBLU"┃"NOR,);
		}	
	}
	if( sizeof(my_other)>=1 )
	{
		if( start!=3 )
			arg+= GRNBLU"┣"NOR HIR" 特殊技能 "NOR "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"GRNBLU"┫"NOR"\n";
		sname  = sort_array( my_other, (: strcmp :) );
		for(i=0; i<sizeof(sname); i++)
		{
			skill = sname[i];
			if( member_array(skill,mapped)!=-1 )
				str = HIC"★"NOR;
			else	str = "  ";
			level = SKILL_D(skill)->level_description(skl[skill]);
			if( !level || !stringp(level) )
				level = skill_level("base", skl[skill]);
			if( lrn[skill] >= ((skl[skill]+1) * 10) )
				color = HIM;
			else	color = NOR;
			if( color!=NOR )
				level = COLOR_D->replace_color(color+COLOR_D->clean_color(level),1);			
			arg+= sprintf("%-2s%2s%-30s%-10s%13s/%13-d%s\n",
					GRNBLU"┃"NOR+" ",
					str+color,
					to_chinese(skill) + " (" + skill + ")",
            				level,
            				ob_query_skill(who,skill,color),
            				(int)lrn[skill],
					GRNBLU"┃"NOR,);
		}	
	}		
	if( sizeof(my_st)>=1 )
	{
		if( start!=4 )
			arg+= GRNBLU"┣"NOR HIW" 神通技能 "NOR "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"GRNBLU"┫"NOR"\n";
		sname  = sort_array( my_st, (: strcmp :) );
		for(i=0; i<sizeof(sname); i++)
		{
			skill = sname[i];
			level = skill_level("shentong", skl[skill]);
			if( lrn[skill] >= ((skl[skill]+1) * 10) )
				color = HIM;
			else	color = NOR;			
			arg+= sprintf("%-2s%2s%-30s%-10s%13s/%13-d%s\n",
					(lrn[skill] >= ((skl[skill]+1) * 10) ) ? GRNBLU"┃"NOR HIM" " : GRNBLU"┃"NOR+" ",
					"  "+color,
					to_chinese(skill) + " (" + skill + ")",
            				level,
            				ob_query_skill(who,skill,color),
            				(int)lrn[skill],
					GRNBLU"┃"NOR,);
		}	
	}
	arg+= GRNBLU"┗━━━━━━━━━━━━━━"HIC"★ 小雨西游 ★"NOR""GRNBLU"━━━━━━━━━━━━━┛"NOR"\n";
	return arg;	
}


int main(object me, string arg)
{
	object ob, *list, couple_ob;
	mapping skl, lrn, map;
	string *sname, *mapped,target,cardname;
	int i, marry_flag;

	seteuid(getuid());

	if(!arg)
		ob = me;
	else{
		ob = present(arg, environment(me));
		if (!ob) ob = find_player(arg);
		if (!ob) ob = find_living(arg);
                if (!ob) ob = LOGIN_D->find_body(arg);
                if (!ob || !me->visible(ob))
                return notify_fail("你要察看谁的技能？\n");
	}
          
	target = (string) me->query("couple/couple_id");	
	if(stringp(target)) couple_ob = find_player(target);
	if( ob!=me && !wizardp(me) && !ob->is_apprentice_of(me)
	&& !me->is_apprentice_of(ob) && ob!=couple_ob
	&& !ob->query("skill_public") )
		return notify_fail("只有管理或有师徒关系的人能察看他人的技能。\n");

	skl = ob->query_skills();
	if(!sizeof(skl)) {
		write( (ob==me ? "你" : ob->name()) + "目前并没有学会任何技能。\n");
		return 1;
	}
	write( "◎"+(ob==me ? HIG"你" : ob->name()) +HIG"目前共学过"HIR+chinese_number(sizeof(skl))+HIG"种技能：\n"NOR);
	arg = who_query_skill(ob);
	me->start_more(arg);
	return 1;
}

string skill_level(string type, int level)
{
	int grade;

        grade = level / 60;

	switch(type) {
		case "knowledge":
			if( grade >= sizeof(knowledge_level_desc) )
				grade = sizeof(knowledge_level_desc)-1;
			return knowledge_level_desc[grade];
		case "shentong" :
			if( grade >= sizeof(shentong_level_desc) )
				grade = sizeof(shentong_level_desc)-1;
			return shentong_level_desc[grade];
		default:
			if( grade >= sizeof(skill_level_desc) )
				grade = sizeof(skill_level_desc)-1;
			return skill_level_desc[grade];
	}
}

int help(object me)
{
	write(@HELP
指令格式 : skills [<某人>]

这个指令可以让你查询所学过的技能。

你也可以指定一个和你有师徒关系的对象，用 skills 可以查知对方的技能状况。


HELP
    );
    return 1;
}

