// chard.c
#include <ansi.h>
#include <mudlib.h>
inherit F_DBASE;

nosave mapping title = ([]);

void init_title();
mixed is_title(string t);

void create() 
{ 
	set("channel_id","称号系统");
	seteuid(getuid()); 
	init_title();
	CHANNEL_D->do_channel(this_object(),"sys","初始化完毕。");
}

void init_title()
{
	int i,v,k;
	string *strs,*str2,*str3,file,temp,name,n,data,prop,ss;
	mapping my;
	if( file_size("/doc/title")<1 )
		return;
	file = read_file("/doc/title");
	if( !file || !stringp(file) )
		return;
	file = replace_string(file,";-----------------------------;~","");
	file = replace_string(file,"\n","");
	strs = explode(file,"~");
	if( !strs || !arrayp(strs) || sizeof(strs)<1 )
		return;
	reset_eval_cost();	
	for(i=0;i<sizeof(strs);i++)
	{
		if( strs[i]=="" )
			continue;
		if( strsrch(strs[i],";")!=-1 )
			continue;
		temp = strs[i];			
		temp = strs[i];
		str2 = explode(temp,"^");
		if( !str2 || !arrayp(str2) || sizeof(str2)<1 )
			continue;
		n = str2[0];
		name = n;
		if( sizeof(str2)<2 )
		{
			title[name] = 0;
			continue;
		}
		temp = str2[1];
		str3 = explode(temp,"$");
		if( !str3 || !arrayp(str3) || sizeof(str3)<1 )	
		{
			title[name] = 0;
			continue;
		}
		my=([]);
		for(k=0;k<sizeof(str3);k++)
		{
			data = str3[k];
			sscanf(data,"%s#%d",data,v);
			if( v<=0 )
				continue;
			if( undefinedp(my[data]) )	
				my[data] = v;
		}
		title[name] = my;
	}
}

mixed is_title(string t)
{
	string *titles;
	int i;
	if( !title || !stringp(t) )
		return 0;
	titles = keys(title);
	if( !titles || !arrayp(titles) || sizeof(titles)<1 )
		return 0;
	for(i=0;i<sizeof(titles);i++)
	{
		if( t==COLOR_D->replace_color(titles[i]) )
			return titles[i];
	}
	return 0;		
}


mixed unequip_title(object who,string old)
{
	mapping prop;
	string *datas,t;
	int i;
	if( !who || !objectp(who) || !stringp(old) )
		return 0;
	if( old!=who->query_temp_title() )
		return 0;
	if( !t=is_title(old) )
		return 0;
	prop = title[t];
	if( !prop || !mapp(prop) )
		return 0;
	datas = keys(prop);
	if( !datas || !arrayp(datas) || sizeof(datas)<1 )
		return 0;
	for(i=0;i<sizeof(datas);i++)
	{
		if( prop[datas[i]]>0 )
		{
			who->add_temp("apply/"+datas[i],-prop[datas[i]]);
			if( who->query_temp("apply/"+datas[i])==0 )
				who->delete_temp("apply/"+datas[i]);
		}	
	}
	CHAR_D->setup_char( who );
	UPDATE_D->check_user(who,1);
	who->save();					
	return t;
}

mixed equip_title(object who,string n)
{
	mapping prop;
	string *datas,t;
	int i;
	if( !who || !objectp(who) || !stringp(n) )
		return 0;
	if( !t=is_title(n) )
		return 0;
	prop = title[t];
	if( !prop || !mapp(prop) )
		return 0;
	datas = keys(prop);
	if( !datas || !arrayp(datas) || sizeof(datas)<1 )
		return 0;
	for(i=0;i<sizeof(datas);i++)
	{
		if( prop[datas[i]]>0 )
			who->add_temp("apply/"+datas[i],prop[datas[i]]);
	}
	CHAR_D->setup_char( who );
	UPDATE_D->check_user(who,1);
	who->save();					
	return t;
}

string c_apply(string arg)
{
	mapping capply = ([
		"spells_def"	: "法术防御",
		"spells_damage"	: "法术攻击",
		"combat_def"	: "物理防御",
		"combat_damage"	: "物理攻击",
		"strength"	: "后天体格",
		"courage"	: "后天胆识",
		"intelligence"	: "后天悟性",
		"spirituality"	: "后天灵性",
		"composure"	: "后天定力",
		"personality"	: "后天魅力",
		"constitution"	: "后天根骨",
		"karma"		: "后天福缘",
		"max_kee"	: "气血后限",
		"max_sen"	: "精神后限",	
		"max_force"	: "内力后限",
		"max_mana"	: "法力后限",
		"max_gin"	: "活力后限",
       		"receive_force"	: "内力自动恢复",
	       	"receive_mana"	: "法力自动恢复",
       		"receive_kee"	: "气血自动恢复",
	       	"receive_sen"	: "精神自动恢复",
       		"reduce_busy"	: "僵直效果减少",
		"re_spells_effdamage" : "法术损伤反弹百分比%",
		"re_combat_effdamage" : "物理损伤反弹百分比%",
       		"attack"	: "攻击命中率%",
       		"defense"	: "攻击闪避率%",
       		"spells_succ"	: "法术命中率%",
       		"spells_dodge"	: "法术闪避率%",
       		"combat_succ"	: "物理命中率%",
       		"combat_dodge"	: "物理闪避率%",
       		"combat_parry"	: "物理招架率%",
       		"force_recover" : "吸气效果追加%",
       		"fofce_refresh"	: "凝神效果追加%",
       		"receive_heal_kee"	: "气血恢复附加率%",
		"receive_heal_sen"	: "精神恢复附加率%",
		"receive_curing_kee"	: "气血治疗附加率%",
       		"receive_curing_sen"	: "精神治疗附加率%",
       		"receive_exercise"	: "打坐恢复附加率%",
		"receive_meditate"	: "冥思恢复附加率%",
		"re_spells_damage" : "法术伤害反弹百分比%",
		"re_combat_damage" : "物理伤害反弹百分比%",       		
	]);
	if( undefinedp(capply[arg]) )
	{
		if( sscanf(arg,"ad_%s",arg)==1 )
		{
			if( is_chinese(to_chinese(arg)) )
				return to_chinese(arg)+"等级";
			else	return arg;	
		}
		else if( is_chinese(to_chinese(arg)) )
			return to_chinese(arg)+"有效等级";
		else	return arg;	
	}
	else	return capply[arg];
}

varargs mixed title_list(mixed raw)
{
	string *strs,arg,str,name,*datas,data;
	int i,k,l;
	mapping prop;
	
	if( !title || !mapp(title) )
		return "暂无信息。\n";
	strs = keys(title);
	if( !strs || !arrayp(strs) || sizeof(strs)<1 )
		return "暂无可用的信息。\n";
	if( raw )
	{
		if( intp(raw) )
			return title;
		if( stringp(raw) )
		{	
			reset_eval_cost();	
			str = "";
			for(i=0;i<sizeof(strs);i++)
			{
				name = strs[i];
				if( COLOR_D->replace_color(name)!=COLOR_D->replace_color(raw) )
					continue;
				str+= sprintf("%20-s",COLOR_D->replace_color(strs[i]));
				prop = title[name];
				if( !prop || !mapp(prop) )
				{
					str+= "暂无\n";
					continue;
				}
				datas = keys(prop);
				if( !datas || !arrayp(datas) || sizeof(datas)<1 )
				{
					str+= "暂无\n";
					continue;
				}
				for(k=0;k<sizeof(datas);k++)
				{
					data = datas[k];
					if( prop[data]!=0 )
					{
						arg = c_apply(data);
						l = strlen(arg);
						if( arg[l-1]=='%' )
							arg = "%";
						else	arg = "点";
						if( i%2==1 )	
							str+= sprintf(CYN"%s%s%3d%s"NOR,c_apply(data),prop[data]>0?"+":"-",prop[data]>=0?prop[data]:-prop[data],arg);
						else	str+= sprintf(YEL"%s%s%3d%s"NOR,c_apply(data),prop[data]>0?"+":"-",prop[data]>=0?prop[data]:-prop[data],arg);	
					}
					str+= "  ";	 
				}
				str+= "\n";
				str = replace_string(str,COLOR_D->replace_color(strs[i]),COLOR_D->replace_color(strs[i],1));
			}
			return str;		
		}
		else	return "";
	}	
	str = MUDLIB_NAME+"目前可选的头衔有"+sizeof(strs)+"个：\n";
	reset_eval_cost();	
	for(i=0;i<sizeof(strs);i++)
	{
		name = strs[i];
		str+= sprintf("%20-s",COLOR_D->replace_color(strs[i]));
		prop = title[name];
		if( !prop || !mapp(prop) )
		{
			str+= "暂无\n";
			continue;
		}
		datas = keys(prop);
		if( !datas || !arrayp(datas) || sizeof(datas)<1 )
		{
			str+= "暂无\n";
			continue;
		}
		for(k=0;k<sizeof(datas);k++)
		{
			data = datas[k];
			if( prop[data]!=0 )
			{
				arg = c_apply(data);
				l = strlen(arg);
				if( arg[l-1]=='%' )
					arg = "%";
				else	arg = "点";
				if( i%2==1 )	
					str+= sprintf(CYN"%s%s%3d%s"NOR,c_apply(data),prop[data]>0?"+":"-",prop[data]>=0?prop[data]:-prop[data],arg);
				else	str+= sprintf(YEL"%s%s%3d%s"NOR,c_apply(data),prop[data]>0?"+":"-",prop[data]>=0?prop[data]:-prop[data],arg);	
			}
			str+= "  ";	 
		}
		str+= "\n";
		str = replace_string(str,COLOR_D->replace_color(strs[i]),COLOR_D->replace_color(strs[i],1));
	}
	return str;
}	
		