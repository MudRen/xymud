//  skill.c
//  This is the standard skill daemon object. All objects defining a skill
//  should inherit this as its skeleton.
#include <ansi.h>
inherit F_CLEAN_UP;

void create()
{
seteuid(getuid());
}

// 判定该技能能否被学习或练习的函数，缺省为1
int valid_learn(object me) { return 1; }

int valid_effect(object me, object weapon, string action_name, int skill) 
{ 
return 1;
}

// type()
// This function should return the type of the skill. The skill type now
// affects if the skill requires combat exp in order to be learned (see
// /cmds/std/learn.c ) and the ranking of a skill level (see 
// /cmds/usr/skills.c )。
// Currently we have only 2 types of skill: "martial" and "knowledge".
string type() { return "martial"; }

// skill_improved()
// This function is called when a character's skill has gained a new level.
// You can make some modify to a character according to the skill.
void skill_improved(object me) {}

// exert_function()
//     This function is used by the "exert" command as specific skill's 
// command parser. This function parses the arguments in the standard form
// (that is, exert <function> [<target>]). When <target> is not present,
// use the character himself as default.
//     In order to use this default exert command parser, you must define
// a function called exert_function_file(string func) in the skill object
// that takes the function name as argument and return the file name that
// defines the specified function. 
string query_name()
{
	int i;
	string *names,name = base_name(this_object());
	names = explode(name,"/");
	i = sizeof(names);
	return names[i-1];
}	

int exert_function(object me, string arg)
{
	string action, target, file,msg;
	object target_ob,ob;

	if( sscanf(arg,"%s %s",action,target)==2 ) 
    	{
    		target_ob = present(target, environment(me));
		if( !target_ob ) 
			return notify_fail("这里没有 " + target + "。\n");
	} 
	else 	action = arg;
	if( !stringp(file = (string)this_object()->exert_function_file(action))
  	|| file_size(file + ".c") <= 0 ) 
	{
    		return 0;
	}
	if( time()<(me->query_temp("no_exert/start")+me->query_temp("no_exert/time")) )
    	{
    		if( stringp(msg=me->query_temp("no_exert/msg")) )
        		return notify_fail(msg+"\n"NOR);
	}
	me->set_temp("kill_msg","exert_"+query_name()+"_"+action);
	return (int)call_other( file, "exert", me, target_ob);	
}

int perform_action(object me, string arg)
{
	string action, target, file,msg;
	object target_ob;

	if( sscanf(arg,"%s %s",action,target)==2 ) 
    	{
    		target_ob = present(target, environment(me));
		if( !target_ob ) 
			return notify_fail("这里没有 " + target + "。\n");
	} 
	else    action = arg;
	if( !stringp(file = (string)this_object()->perform_action_file(action))
  	|| file_size(file + ".c") <= 0 ) 
	{
    		return 0;
	}
	if( time()<(me->query_temp("no_perform/start")+me->query_temp("no_perform/time")) )
    	{
    		if( stringp(msg=me->query_temp("no_perform/msg")) )
        		return notify_fail(msg+"\n"NOR);
        	else	return notify_fail("你现在不能施展外功。\n");	
	}
	me->set_temp("kill_msg","perform_"+action);
	return (int)call_other( file, "perform", me, target_ob);
}

int cast_spell(object me, string arg)
{
	string action, target, file,msg;
	object target_ob;

	if( sscanf(arg,"%s %s",action,target)==2 ) 
    	{
    		target_ob = present(target, environment(me));
		if( !target_ob ) 
			return notify_fail("这里没有 " + target + "。\n");
	} 
	else    action = arg;
	if( !stringp(file = (string)this_object()->cast_spell_file(action))
  	|| file_size(file + ".c") <= 0 ) 
	{
    		return 0;
	}
	if( time()<(me->query_temp("no_cast/start")+me->query_temp("no_cast/time")) )
    	{
    		if( stringp(msg=me->query_temp("no_cast/msg")) )
        		return notify_fail(msg+"\n"NOR);
        	else	return notify_fail("你现在不能施展法术。\n");	
	}
	me->set_temp("kill_msg","cast_"+action);
	return (int)call_other( file, "cast", me, target_ob);
}
/*
int cast_spell(object me, string spell, object target)
{
	int tt;
	string file,msg;

	if( !stringp(file = (string)this_object()->cast_spell_file(spell))
  	 || file_size(file + ".c") <= 0 )
		return 0;
	if( time()<(me->query_temp("NoCast/start")+me->query_temp("NoCast/time")) )
    {
    	if( stringp(msg=me->query_temp("NoCast/msg")) )
        	return notify_fail(msg+"\n"NOR);
	}
	me->set_temp("kill_msg","cast_"+spell);
	tt =  (int)call_other( file, "cast", me, target);
	if( tt>0 )
	{
       		me->set_temp("no_cast",time());
			me->set_temp("no_cast_time",tt);
			return 1;
	}
	else
		return 0;
}
*/
int conjure_magic(object me, string magic, object target)
{
	string file;
	notify_fail("你所选用的法术系中没有这种法术。\n");

	if( !stringp(file = (string)this_object()->conjure_magic_file(magic))
 	 || file_size(file + ".c") <= 0 )
		return 0;
	me->set_temp("kill_msg","conjure"+magic);		
	return (int)call_other( file, "conjure", me, target);
}

int scribe_spell(object me, object ob, string spell)
{
	string file;
	if( !stringp(file = (string)this_object()->scribe_spell_file(spell))
 	 || file_size(file + ".c") <= 0 )
		return 0;
	me->set_temp("kill_msg","scribe"+spell);	
	return (int)call_other( file, "scribe", me, ob );
}

//weiqi, 981115
//string level_description(int level)
//this function is to allow customerized description of skill level...
//just override this default one.
string level_description(int level)
{
	int grade;
	string *skill_level_desc = ({
        BLU "初学乍练" NOR,
        BLU "初窥门径" NOR,
        HIB "粗通皮毛" NOR,
        HIB "略知一二" NOR,
        YEL "半生不熟" NOR,
        YEL "马马虎虎" NOR,
        HIY "已有小成" NOR,
        HIY "渐入佳境" NOR,
        HIM "驾轻就熟" NOR,
        HIM "了然于胸" NOR,
        HIR "出类拔萃" NOR,
        HIR "心领神会" NOR,
        MAG "神乎其技" NOR,
        MAG "出神入化" NOR,
        CYN "豁然贯通" NOR,
        CYN "登峰造极" NOR,
        HIC "举世无双" NOR,
        HIC "一代宗师" NOR,
        HIC "震古铄今" NOR,
        HIW "深不可测" NOR
    });
	string *knowledge_level_desc = ({
        BLU "新学乍用" NOR,
        HIB "初窥门径" NOR,
        HIB "略知一二" NOR,
        YEL "马马虎虎" NOR,
        YEL "已有小成" NOR,
        CYN "心领神会" NOR,
        CYN "了然于胸" NOR,
        CYN "豁然贯通" NOR,
        HIC "举世无双" NOR,
        HIC "震古铄今" NOR,
        HIW "深不可测" NOR
    });

	grade = level /120;

	switch(type()) 
    {
    	case "knowledge":
        	if( grade >= sizeof(knowledge_level_desc) )
            	grade = sizeof(knowledge_level_desc)-1;
			return knowledge_level_desc[grade];
        default:
            if( grade >= sizeof(skill_level_desc) )
            	grade = sizeof(skill_level_desc)-1;
			return skill_level_desc[grade];
	}
}

int NewRandom(int n, int base, int d)
{
        int sum;
        int i;
        int k;

        k = 6;
        if (k > n) k = n;
        if (! k) return n;

        sum = 0;
        for (i = 0; i < k; i++) sum += i;
        sum = random(sum);
        for (i = 0; i < k; i++)
        {
                sum -= i;
                if (sum <= 0)
                {
                        n = n - k + i;
                        if (n <= 0) n = 0;
                        break;
                }
        }
        return n;
}