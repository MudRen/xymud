inherit F_CLEAN_UP;
#include <ansi.h>;

string 	*HP = ({
		"kee","eff_kee","kee_ratio",
		"sen","eff_sen","sen_ratio",
		"mana","force","max_force","max_mana",
		"force_ratio","mana_ratio",
		"water","food","bellicosity",
		"combat_exp","daoxing","potential",
});
string *Score = ({
		"title","name","id","combat_damage","combat_def",
		"spells_damage","spells_def","family","master",
		"int","spi","cor","str","cps","per","con","kar",
		"age","balance","money",
});
string *Room = ({
		"short","exits","outdoors","no_fight","no_magic","water",
});				

int help (object me)
{
        write(@HELP
指令格式：  
	query [标题]:<参数>  
   根据输入的参数来统计当前人物或区域相应的值，并以标题开头返回
   多个参数时，以,格开
   当不叫标题时，默认标题为：小雨西游
举例：
        query HP:kee,name,have(huicheng juan),skill(force)
将会返回
>HP：2880,眼免,2,1200|1200|ningxie-force

具体参数如下：
   气血精神信息：kee,sen,eff_kee,eff_sen,kee_ratio,sen_ratio,
   内力法力信息：force,mana,max_force,max_mana,force_ratio,mana_ratio,
   饮食杀气信息：water,food,bellicosity,
   武学道行潜能：combat_exp,daoxing,potential,
   称号姓名信息：title,name,id,
   攻防属性信息：combat_damage,combat_def,spells_damage,spells_def,
   师门师傅信息：family,master,age,
   后天天赋信息：int,spi,cor,str,cps,per,con,kar,
   金钱存款信息：balance,money,
   身上物品数量：count(查询物品的id),
   区域属性信息：short,exits,outdoors,no_fight,no_magic,water,
                 have(NPC的id),
   技能等级激发：skill(查询技能的id)

HELP
);
        return 1;
}

mixed _query_hp(object me,string arg)
{
	if( member_array(arg,HP)==-1 )
		return 0;
	if( wizardp(me) && me->query("env/test") )
		tell_object(me,"_query_hp arg="+arg+"\n");		
	if( arg=="potential" )
		return (int)me->query("potential")-(int)me->query("learned_points");
	else if( arg!="kee_ratio" && arg!="sen_ratio" 
	      && arg!="mana_ratio" && arg!="force_ratio" )
		return me->query(arg);
	switch(arg)
	{	
		case "kee_ratio" :return me->query("eff_kee")*100/me->query_maxkee();
		case "sen_ratio" :return me->query("eff_sen")*100/me->query_maxsen();
                case "force_ratio" : return (me->query_maxforce()>0?me->query("force")*100/me->query_maxforce():0);
		case "mana_ratio" : return me->query("mana")*100/me->query_maxmana();
		default : return 0;
	}	
}

mixed _query_score(object me,string arg)
{
	if( wizardp(me) && me->query("env/test") )
		tell_object(me,"_query_score arg="+arg+"\n");		
	if( member_array(arg,Score)==-1 )
		return 0;
	switch(arg)
	{
		case "title" : return me->query("title")?me->query("title"):me->query_title();
		case "name"  : return me->query("name");
		case "id"    : return me->query("id");
		case "combat_damage" : return me->query_combat_damage();
		case "combat_def"    : return me->query_combat_def();
		case "spells_damage" : return me->query_spells_damage();
		case "spells_def"    : return me->query_spells_def();
		case "family"	     : return me->query("family/family_name");	
		case "master"	: return me->query("family/master_name");
		case "int"	: return me->query_int();
		case "spi"	: return me->query_spi();
		case "cor"	: return me->query_cor();
		case "str"	: return me->query_str();
		case "cps"	: return me->query_cps();
		case "per"	: return me->query_per(); 
		case "con"	: return me->query_con();
		case "kar"	: return me->query_kar();
		case "age"	: return me->query("age");
		case "balance"  : if( me->check_balance(1) ) return me->query_balance();
				  else return 0;
		case "money"    : return me->query_money();
		default : return 0;
	}			
}

int _query_item(object me,string arg)
{
	object *inv;
	int i,f=0;
	if( wizardp(me) && me->query("env/test") )
		tell_object(me,"_query_item arg="+arg+"\n");		
	inv = all_inventory(me);
	if( !inv || sizeof(inv)<1 )
		return 0;
	for(i=0;i<sizeof(inv);i++)
	{
		if( member_array(arg,inv[i]->parse_command_id_list())!=-1 )	
		{
			if( inv[i]->query_amount()<1 )
				f++;
			else	f+= inv[i]->query_amount();
		}
	}
	return f;
}		

mixed _query_room(object me, string arg)
{
	string msg;
	mixed str;
	int i;
	object env;
	if( wizardp(me) && me->query("env/test") )
		tell_object(me,"_query_room arg="+arg+"\n");		
	if( member_array(arg,Room)==-1 )
		return 0;
	if( !objectp(env=environment(me)) )
		return 0;
	str = env->query(arg);
	if( !str )
		return 0;
	else if( stringp(str) )
		return str;
	else if( arrayp(str) )
	{
		if( sizeof(str)<1 )
			return 0;
		msg = "";
		for(i=0;i<sizeof(str);i++)
		{
			msg+= str[i]+"";
			if( i<sizeof(str)-1 )
				msg+= "|";
		}
		return msg;
	}
	else if( mapp(str) )
	{
		str = keys(str);
		if( !str || !arrayp(str) || sizeof(str)<1 )
			return 0;
		msg = "";
		for(i=0;i<sizeof(str);i++)
		{
			msg+= str[i]+"";
			if( i<sizeof(str)-1 )
				msg+= "|";
		}
		return msg;
	}
	else	return 0;		
}

mixed _query_npc(object me,string arg)
{
	string msg;
	object *inv,env;
	int i,k;
	if( wizardp(me) && me->query("env/test") )
		tell_object(me,"_query_npc arg="+arg+"\n");	
	if( !objectp(env=environment(me)) )
		return "no env";
	inv = all_inventory(env);
	if( !inv || sizeof(inv)<1 )
		return "no inv";
	msg = "";
	k = 0;	
	for(i=0;i<sizeof(inv);i++)
	{
		if( inv[i]==me )
			continue;
		if( member_array(arg,inv[i]->parse_command_id_list())!=-1 )
		{
			msg+= inv[i]->name();
			k++;
		}
		else	continue;	
                if( k<sizeof(inv)-1 && k>0 )
			msg+= "|";	
	}
	return msg;		
}

mixed _query_skill(object me,string arg)
{
	string msg,mp_skill;
	if( wizardp(me) && me->query("env/test") )
		tell_object(me,"_query_skill arg="+arg+"\n");		
	if( file_size(SKILL_D(arg+".c"))<1 )
		return "没有名为"+arg+"的技能";
	if( me->query_skill(arg,2)<1 )
		return "你没有学习这项技能";
	msg = sprintf("%d",me->query_skill(arg,1));
	if( stringp(mp_skill=me->query_skill_mapped(arg)) )
		msg+= "|"+me->query_skill(mp_skill,1)+"|"+mp_skill;
	else	msg+= "|0|0";
	return msg;
}

int main(object me, string arg)
{
	string qst,*msg,str,tmp;
	int i;
	if( !arg )
		return help(me);
        if( strlen(arg)>200 )
		return notify_fail("输过信息过长，不符合国情！\n");		
	if( sscanf(arg,"%s:%s",qst,arg)!=2 )
		qst = "小雨西游";
	str = qst+"：";	
	if( strsrch(arg,",")==-1 )
	{
		if( member_array(arg,HP)!=-1 )
			str+= _query_hp(me,arg);
		else if( member_array(arg,Score)!=-1 )		
			str+= _query_score(me,arg);
		else if( member_array(arg,Room)!=-1 )
			str+= _query_room(me,arg);
		else if( sscanf(arg,"count(%s)",arg)==1 )
			str+= _query_item(me,arg)+"";	
		else if( sscanf(arg,"have(%s)",arg)==1 )
			str+= _query_npc(me,arg);	
		else if( sscanf(arg,"skill(%s)",arg)==1 )
			str+= _query_skill(me,arg);
		else	str+= "0";	
	}
	else
	{		
		msg = explode(arg,",");
		for(i=0;i<sizeof(msg);i++)
		{
			tmp = msg[i];
			if( member_array(tmp,HP)!=-1 )
				str+= _query_hp(me,tmp);
			else if( member_array(tmp,Score)!=-1 )		
				str+= _query_score(me,tmp);
			else if( member_array(tmp,Room)!=-1 )
				str+= _query_room(me,tmp);
			else if( sscanf(tmp,"count(%s)",tmp)==1 )
				str+= _query_item(me,tmp)+"";	
			else if( sscanf(tmp,"have(%s)",tmp)==1 )
				str+= _query_npc(me,tmp);	
			else if( sscanf(tmp,"skill(%s)",tmp)==1 )
				str+= _query_skill(me,tmp);
			else	str+= "0";
			if( i<sizeof(msg)-1 )
				str+= ",";
		}
	}	
	str+="\n";
	write(str);				
	return 1;			
}


