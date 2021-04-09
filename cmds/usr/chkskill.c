// chkskill.c
#include "/doc/help.h"
#include <ansi.h>
inherit F_CLEAN_UP;

string *basic_skill = ({ 
  "axe",
  "blade",
  "dagger",
  "dodge",
  "force",
  "fork",
  "hammer",
  "mace",
  "parry",
  "rake",
  "spear",
  "spells",
  "staff",
  "stick",
  "sword",
  "throwing",
  "unarmed",
  "whip",
});

string Check_skill(string arg,string type)
{
	int i,w,j;
	string dir,msg,tmp;
	mixed *file;
	if( !arg )
		return 0;
	switch(type)
	{
		case "force" :
			msg = NOR"│"+sprintf(" "HIC"%55-s"NOR"│\n│","特殊运用 (exert)");
			dir = SKILL_D(arg)->exert_function_file("");
			if( dir )
				file = get_dir(dir,-1);
			else	return "目前「"+to_chinese(arg)+"」没有任何特殊内功运用。\n";	
			i = sizeof(file);
			w = 0;
			if( sizeof(file)<=0 ) 
		 		return "目前「"+to_chinese(arg)+"」没有任何特殊内功运用。\n";
		 	tmp = "内功";	
			break;
		case "spells" :
			msg = NOR"│"+sprintf(" "HIC"%55-s"NOR"│\n│","特殊运用 (cast)");
			dir = SKILL_D(arg)->cast_spell_file("");
			if( dir)
				file = get_dir(dir, -1);			
			else	return "目前「"+to_chinese(arg)+"」没有任何特殊法术运用。\n";	
			i = sizeof(file);
			w = 0;
			if( sizeof(file)<=0 ) 
		 		return "目前「"+to_chinese(arg)+"」没有任何特殊法术运用。\n";
		 	tmp = "法术";	
			break;
		case "perform" : 
			msg = NOR"│"+sprintf(" "HIC"%55-s"NOR"│\n│","特殊运用 (perform)");
			dir = SKILL_D(arg)->perform_action_file("");
			if( dir )
				file = get_dir(dir, -1);
			else	return "目前「"+to_chinese(arg)+"」没有任何特殊外功运用。\n";	
			i = sizeof(file);
			w = 0;
			if( sizeof(file)<=0 ) 
		 		return "目前「"+to_chinese(arg)+"」没有任何特殊外功运用。\n";
		 	tmp = "外功";	
			break;	
		default : return 0;
	}	
	for(j = 0; j<i;j++ ) 
	{
		if(file[j][0][strlen(file[j][0])-2..strlen(file[j][0])] != ".c") 
			continue; 
		file[j][0]= replace_string(file[j][0],".c","");
		
		msg+= sprintf("   "HIR"%15-s",file[j][0]);
//		msg = sprintf("%s│"HIR"%-15s",msg,file[j][0]);
		w++; 
		if( w%4==3 )
			msg+= NOR"  │\n│";
	}
	if( w%2==0 && w>2 )
		msg+= NOR"                                      │";
	else if( w==2 )			
		msg+= NOR"                    │";
	msg += NOR"\n";
	if( w==0 ) 
		msg+= NOR"│"+sprintf(" "HIG"%43-s"NOR"正在整理中。│\n","「"+to_chinese(arg)+"」");
	else	msg+= NOR"│"+sprintf(" "HIG"%55-s"NOR"│\n","「"+to_chinese(arg)+"」目前共有"+chinese_number(w)+"种"+"特殊"+tmp+"运用。"); 
	return msg;
}

int main(object me, string arg)
{
	int i, j, w, val;
	string dir,msg,tmp;
	mapping skl,lrn;

	seteuid(getuid());

	if( !arg ) 
		return notify_fail("指令格式：chkskill <skill>\n");

	skl = me->query_skills();
	lrn = me->query_learned();
	if( !skl ) 
		return notify_fail("你目前并没有学会任何技能。\n");
	if( undefinedp(skl[arg]) 
	 || skl[arg]<=0 )
		return notify_fail("你不会这种技能。\n");
	msg = NOR"\n┌────────────────────────────┐\n"NOR;
	msg+= "│"HIG+sprintf(" %55-s"NOR"│\n",to_chinese(arg)+" ("+arg+") ");
	msg+= NOR"├────────────────────────────┤\n";
	msg+= "│ 等  级："HIY+sprintf(" %16-d"NOR"升级熟练度："HIY"%3d%%"NOR"              │\n",skl[arg],100*(int)lrn[arg]/(int)((skl[arg]+1)*(skl[arg]+1)));
                		
	val = sizeof(basic_skill);
	while(val--) 
	{
		if( SKILL_D(arg)->valid_enable(basic_skill[val])) 
		{
			w++;
			msg+= NOR"│";
			if(w==1) 	
				msg+= " 用  途： "CYN;
			else	msg+= "          "CYN;
			msg+= sprintf("%46-s"NOR"│\n",to_chinese(basic_skill[val])+" ("+basic_skill[val]+")");
			
		}
	}
	if( w>0 )
		msg+= NOR"├────────────────────────────┤\n";
	if(SKILL_D(arg)->type() == "knowledge" ) 
	{
		msg+= NOR"└────────────────────────────┘\n";
		msg+= "「"+to_chinese(arg)+"」不属于武技，没有特殊攻击或者运用。\n";
		write(msg);
		return 1; 
	}
	if(SKILL_D(arg)->type() == "shentong" ) 
	{
		msg+= NOR"└────────────────────────────┘\n";
		msg+= "「"+to_chinese(arg)+"」是被动性神通技能，没有特殊攻击或者运用。\n";
		write(msg);
		return 1; 
	}
	if(member_array(arg, basic_skill)!= -1) 
	{
		msg+= NOR"└────────────────────────────┘\n";
		if( arg=="force" )
			msg+= NOR" 基本内功公共类运用："HIC"\n  吸气：exert recover   凝神：exert refresh\n"NOR;
		else if( arg=="spells" )
			msg+= NOR" 基本法术公共类运用："HIC"\n  法力转内力：cast transfer   元神出窍：cast chuqiao\n  筑基小神通：cast xiaoshen\n"NOR;
		else	msg+= "「"+to_chinese(arg)+"」属于基本技能，没有特殊攻击或者运用。\n";
		write(msg);
		return 1; 
	}

	tmp = "";
	if(SKILL_D(arg)->valid_enable("force") )	 
	{
		if( stringp(dir=Check_skill(arg,"force")) )
		{
			tmp+= dir;	
			tmp+= NOR"├────────────────────────────┤\n";
		}
	}
	if(SKILL_D(arg)->valid_enable("spells") )	 
	{
		if( stringp(dir=Check_skill(arg,"spells")) )
		{
			tmp+= dir;	
			tmp+= NOR"├────────────────────────────┤\n";
		}
	}
	if( stringp(dir=Check_skill(arg,"perform")) )
	{
		tmp+= dir;	
		//tmp+= NOR"├────────────────────────────┤\n";
	}
	
	if( tmp=="" )
	{
		msg+= NOR"└────────────────────────────┘\n";
		msg+= "目前「"+to_chinese(arg)+"」没有任何特殊作用。\n";
		write(msg);
		return 1; 
	}
	//msg+= NOR"├────────────────────────────┤\n";
	msg+= tmp;
	msg+= NOR"└────────────────────────────┘\n";
	write(msg);
	return 1;	
}

int help(object me)
{
	write(@HELP
指令格式: chkskill [<功夫名>]
 
列出这种功夫所有的特殊攻击，前题是你必须会这项技能。 

范例：
chkskill huashan-jianfa  

会列出所有华山剑法的状态和特殊攻击。 
 
HELP
	);
	return 1;
}
