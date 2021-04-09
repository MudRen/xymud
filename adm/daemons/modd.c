#include <ansi.h>
#include <mudlib.h>
inherit F_DBASE;

nosave mapping mods = ([]);

void init_mod();
mixed is_title(string t);

void create() 
{ 
	set("channel_id","套装系统");
	seteuid(getuid()); 
	init_mod();
	CHANNEL_D->do_channel(this_object(),"sys","初始化完毕。");
}

mapping query_mods(){return mods;}

void equip_mod(object who,object obj);

void init_mod()
{
	int i,k,p;
	string *strs,file,*str2,*need,name,title,tmp,*temp,apply;
	mapping prop;
	if( file_size("/doc/mod")<1 )
		return;
	file = read_file("/doc/mod");
	if( !file || !stringp(file) )
		return;
	file = replace_string(file,"\n","");
	file = replace_string(file,";-----------------------------;~","");
	strs = explode(file,"^");
	if( !strs || !arrayp(strs) || sizeof(strs)<1 )
		return;
	reset_eval_cost();
	mods = ([]);
	for(i=0;i<sizeof(strs);i++)
	{
		if( strs[i]=="" || strlen(strs[i])<4 )
			continue;
		if( strsrch(strs[i],";")!=-1 )
			continue;	
		str2 = explode(strs[i],"&");
		if( !str2 || !arrayp(str2) || sizeof(str2)<1 )
			continue;
		need = ({});
		prop = ([]);	
		tmp = str2[0];
		if( sscanf(tmp,"%s#%s",name,title)!=2 )
			continue;
		title = COLOR_D->replace_color(title,2)+NOR;
		//*
		tmp = str2[1];
		temp = explode(tmp,"|");
		if( !temp || !arrayp(temp) || sizeof(temp)<1 )
			continue;
		for(k=0;k<sizeof(temp);k++)
			need+= ({temp[k]});
		//*
		tmp = str2[2];
		temp = explode(tmp,"|");
		if( !temp || !arrayp(temp) || sizeof(temp)<1 )
			continue;	 
		for(k=0;k<sizeof(temp);k++)
		{
			if( sscanf(temp[k],"%s#%d",apply,p)!=2 )
				continue;
			prop[apply] = p;
		}
		//*
		mods[name] = ([
			"title" : title,
			"need"  : need,
			"prop"  : prop,
		]);		
	}
}

mixed is_mod(mixed t)
{
	mapping this_mod;
	string *list,*mlist,type,title;
	int i;
	if( !mods || sizeof(mods)<1 )
		return 0;
	list = keys(mods);
	if( !list || !arrayp(list) || sizeof(list)<1 )
		return 0;
	if( objectp(t) )
		title = COLOR_D->clean_color(t->query("armor_title"));
	else if( stringp(t) )
		title = COLOR_D->clean_color(t);
	else	return 0;
	if( !title || !stringp(title) )
		return 0;
	if( member_array(title,list)==-1 )
		return 0;

	this_mod = mods[title];
	if( !this_mod || !mapp(this_mod) || sizeof(this_mod)<1 )
		return 0;
	if( undefinedp(this_mod["need"]) )
		return 0;
	if( objectp(t) )
	{
		if( !stringp(type=t->query("armor_type")) )
			return 0;
		if( member_array(type,this_mod["need"])==-1 )
			return 0;				
	}
	return title;		
}

int query_mod_level(object who,string t)
{
	int i,lvl,n;
	object *armors,jia;
	string title,type;
	if( !who || !objectp(who) 
	 || !who->is_character() )
	 	return 0;
	if( !mods || !mapp(mods) || sizeof(mods)<1 )
		return 0;	
	if( !t || !stringp(t) || !is_mod(t) )
		return 0;
	armors = all_inventory(who);
	if( !armors || !arrayp(armors) || sizeof(armors)<1 )
		return 0;
	lvl = n = 0;	
	for(i=0;i<sizeof(armors);i++)
	{
		jia = armors[i];
		if( !jia || !stringp(type=jia->query("armor_type"))
		 || !stringp(title=jia->query("armor_title"))
		 || title!=t )
			continue;
		if( member_array(type,mods[title]["need"])==-1 )
			continue;	
		n++;
		lvl+= jia->query("level");
	}
	if( lvl==0 || n==0 )
		return 0;
	return lvl/n;
}

int query_mod_num(string title)
{
	string *need;
	if( !mods || !mapp(mods) || sizeof(mods)<1 )
		return 0;
	if( !is_mod(title) )
		return 0;	
	need = mods[title]["need"];
	return sizeof(need);
}

mixed check_mod_num(object who,string title)
{
	int i;
	object *inv,jia,*my_mod;
	string  type;
	if( !who || !objectp(who) 
	 || !who->is_character() 
	 || !title || !stringp(title) 
	 || !is_mod(title) )
	 	return 0;
	if( !mods || !mapp(mods) || sizeof(mods)<1 )
		return 0;	 	
	inv = all_inventory(who);
	if( !inv || !arrayp(inv) || sizeof(inv)<1 )
		return 0;
	my_mod = ({});
	for(i=0;i<sizeof(inv);i++)
	{
		jia = inv[i];
		if( !jia || !stringp(type=jia->query("armor_type"))
		 || !jia->query("armor_prop") )
		 	continue;
		 if( !jia->query("armor_title") )
			continue;
		if( jia->query("armor_title")!=title )
			continue;
		if( member_array(type,mods[title]["need"])==-1 )
			continue;
		my_mod+= ({jia});
	}
	if( sizeof(my_mod)>0 )
		return my_mod;
	else	return 0;	
}

mixed mod_equip_num(object who,string title)
{
	int i,f=0;
	object jia,*my_mod;
	string  type;
	my_mod = check_mod_num(who,title);
	if( !my_mod || !arrayp(my_mod) || sizeof(my_mod)<1 )
		return 0;
	for(i=0;i<sizeof(my_mod);i++)
	{
		jia = my_mod[i];
		if( !jia || !stringp(type=jia->query("armor_type"))
		 || !jia->query("armor_prop")
		 || !jia->query("equipped") 
		 || !jia->query("armor_title") 
		 || jia->query("armor_title")!=title )
			continue;
		if( member_array(type,mods[title]["need"])==-1 )
			continue;
		f++;
	}
	return f;
}

void mod_unequip(object who,string title)
{
	string *prop;
	int i;
	mapping old_mod,app;
	if( !mods || !mapp(mods) || sizeof(mods)<1 )
		return;
	if( !is_mod(title) 
	 || undefinedp(mods[title]) )
		return;	
	if( !mapp(old_mod=who->query_temp("MOD")) )
		return;
	if( undefinedp(old_mod[title]) )
		return;
	if( !mapp(old_mod=old_mod[title]) )
	{
		map_delete(who->query_temp("MOD"),title);
		return;
	}	 	
	if( undefinedp(old_mod["apply"]) )
	{
		map_delete(who->query_temp("MOD"),title);
		return;
	}	 	
	if( !mapp(app=old_mod["apply"]) )
	{
		map_delete(who->query_temp("MOD"),title);
		return;
	}	 	
	if( !arrayp(prop=keys(app)) 
	 || sizeof(prop)<1 )
	{
		map_delete(who->query_temp("MOD"),title);
		return;
	}	 	
	for(i=0;i<sizeof(prop);i++)
		who->add_temp("apply/"+prop[i],-app[prop[i]]);
	map_delete(who->query_temp("MOD"),title);
	if( sizeof(who->query_temp("MOD"))<1 )
		who->delete_temp("MOD");
	return;
}

mixed unequip_mod(object who,object obj)
{
	string title,*types,type;
	object *old,*armors;
	int i;
	if( !mods || !mapp(mods) || sizeof(mods)<1 )
		return;
	if( !stringp(title=obj->query("armor_title")) 
	 || !is_mod(title) 
	 || undefinedp(mods[title]) )
		return;
	if( !is_mod(obj) )
		return;		
	if( !who->query_temp("MOD")
	 || !who->query_temp("MOD/"+title) )
	 	return;
	types = mods[title]["need"];
	if( !types || !arrayp(types) || sizeof(types)<2 )
		return;
	if( !stringp(type=obj->query("armor_type")) 
	 || member_array(type,types)==-1 )
	 	return;
	old = who->query_temp("MOD/"+title+"/obj");
	if( !old || !arrayp(old) || sizeof(old)<2 )
	{
		mod_unequip(who,title);
		return;
	}
	if( member_array(obj,old)==-1 )
	{
		log_file("mod",sprintf("%s 身上的 %s套装有问题:装备了的未算入OBJ阵列.\n",who->query("id"),title));
		return;
	}
	mod_unequip(who,title);
	armors = values(who->query_temp("armor"));
	if( !armors || !arrayp(armors) || sizeof(armors)<2 )
		return;
	reset_eval_cost();
	for(i=0;i<sizeof(armors);i++)
	{
		if( stringp(title=armors[i]->query("armor_title")) 
		 && is_mod(title) 
		 && !undefinedp(mods[title]) )
		 	equip_mod(who,obj);	
	}		
}

void equip_mod(object who,object obj)
{
	mapping old_mod,app;
	int now_num,max_num,i,v,p;
	object *have,*armors,*tmp;
	string title,*prop,type;
	if( !mods || !mapp(mods) || sizeof(mods)<1 )
		return;
	if( !stringp(title=obj->query("armor_title")) 
	 || !is_mod(obj) 
	 || undefinedp(mods[title]) )
		return;
	now_num = mod_equip_num(who,title);
	max_num = query_mod_num(title);
	if( now_num<1 )
		return;
		
	have = who->query_temp("MOD/"+title+"/obj");
	if( have && arrayp(have) )
	{
		if( sizeof(have)<1 )	
			mod_unequip(who,title);
		else if( member_array(obj,have)!=-1 )
		{
			log_file("mod",sprintf("%s 身上的 %s套装有问题:未装备的已算入OBJ阵列.\n",who->query("id"),title));
			return;
		}	
		else
		{
			tmp = have;
			have+= ({obj});
			if( sizeof(have)<max_num
			 && sizeof(tmp)>=max_num/2 )
			{
				who->set_temp("MOD/"+title+"/obj",have);
				return;
			}
			else
			{
				mod_unequip(who,title);
				who->set_temp("MOD/"+title+"/obj",have);
				app = mods[title]["prop"];
				prop = keys(app);
				v = query_mod_level(who,title);
				for(i=0;i<sizeof(prop);i++)
				{
					if( member_array(prop[i],keys(("/cmds/std/look.c")->query_euqip_look2()))!=-1 )
					{
						p = app[prop[i]];
						if( now_num>=max_num/2 && now_num!=max_num && now_num>1 )
							p = 0;
					}
					else
					{
						p = app[prop[i]]+v*3;
						if( now_num>=max_num/2 && now_num!=max_num && now_num>1 )
							p = p/2;
					}
					if( p!=0 )
					{
						who->add_temp("apply/"+prop[i],p);
						who->add_temp("MOD/"+title+"/apply/"+prop[i],p);
					}	
				}
				return;
			}
		}
	}
	have = ({});
	armors = values(who->query_temp("armor"));
	for(i=0;i<sizeof(armors);i++)
	{
		if( armors[i]->query("armor_title")==title
		 && stringp(type=armors[i]->query("armor_type"))
		 && member_array(type,mods[title]["need"])!=-1 )
			have+= ({armors[i]});
	}
	who->set_temp("MOD/"+title+"/obj",have);
	if( sizeof(have)<2 )
		return;
	app = mods[title]["prop"];
	prop = keys(app);
	v = query_mod_level(who,title);
	for(i=0;i<sizeof(prop);i++)
	{
		if( member_array(prop[i],keys(("/cmds/std/look.c")->query_euqip_look2()))!=-1 )
		{
			p = app[prop[i]];
			if( now_num>=max_num/2 && now_num!=max_num && now_num>1 )
				p = 0;
		}
		else
		{
			p = app[prop[i]]+v*3;
			if( now_num>=max_num/2 && now_num!=max_num && now_num>1 )
				p = p/2;
		}
		if( p!=0 )
		{
			who->add_temp("apply/"+prop[i],p);
			who->add_temp("MOD/"+title+"/apply/"+prop[i],p);
		}	
	}
	return;
}

string c_apply(string arg)
{
	mapping capply = ("/cmds/std/look.c")->query_euqip_look();
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

int check_mod_type(object who,string title,string type)
{
	string *n_types;
	object *have;
	int i;
	if( !mods || !mapp(mods) || sizeof(mods)<1 )
		return 0;
	if( !title || !stringp(title) )
		return 0;	
	if( undefinedp(mods[title]) )
		return 0;	
	have = check_mod_num(who,title);
	if( !have || !arrayp(have) || sizeof(have)<1 )
		return 0;
	n_types = mods[title]["need"];	
	if( member_array(type,n_types)==-1 )
		return 0;
	for(i=0;i<sizeof(have);i++)		  	
	{
		if( !have[i]->query("equipped")
		  || have[i]->query("equipped")!="worn" )
		  	continue; 
		if( have[i]->query("armor_type")==type )
			return 1;
	}		
	return 0;
}

varargs mixed mod_statue(object who,mixed raw)
{
	string *strs,arg,str,name,*datas,data,title,tmp;
	int i,k,l,now_num,max_num,v,p;
	object *have;
	mapping prop;
	
	if( !mods || !mapp(mods) || sizeof(mods)<1 )
		return "暂无信息。\n";
	strs = keys(mods);
	if( !strs || !arrayp(strs) || sizeof(strs)<1 )
		return "暂无可用的信息。\n";
	if( raw )
	{
		if( intp(raw) )
			return mods;
		if( stringp(raw) )
		{	
			if( !is_mod(raw) || undefinedp(mods[raw]) )
				return 0;
			have = check_mod_num(who,raw);
			if( !have || !arrayp(have) )
				return 0;
			now_num = mod_equip_num(who,raw);
			max_num = query_mod_num(raw);
				
			str = "\n\n\n\n";	
			name = mods[raw]["title"];
			str+= sprintf("  %s("HIC"%d/%d"NOR")",COLOR_D->replace_color(name,1),now_num,max_num);
			if( now_num<2 )
				str+= " "HIY"【"NOR YEL"未激活"NOR HIY"】"NOR"\n";
			else if(now_num<max_num/2 )
				str+= " "HIY"【"NOR YEL"未激活"NOR HIY"】"NOR"\n";
			else if(now_num==max_num )	
				str+= " "HIY"【"NOR HIG"激  活"NOR HIY"】"NOR"\n";
			else	str+= " "HIY"【"NOR HIG"激活(效果减半)"NOR HIY"】"NOR"\n";			
			datas = mods[raw]["need"];
			reset_eval_cost();
			for(i=0;i<sizeof(datas);i++)
			{
				if( check_mod_type(who,raw,datas[i]) )
					str+= "      "NOR+HIG+("/cmds/std/look.c")->armor_type(datas[i])+NOR;
				else	str+= "      "NOR+CYN+("/cmds/std/look.c")->armor_type(datas[i])+NOR;
				str+= "\n";
			}
			prop = mods[raw]["prop"];
			datas = keys(prop);	
			v = query_mod_level(who,raw);
			for(i=0;i<sizeof(datas);i++)
			{
				data = datas[i];
				if( member_array(data,keys(("/cmds/std/look.c")->query_euqip_look2()))!=-1 )
				{
					arg = "%";
					p = prop[data];
					if( now_num>=max_num/2 && now_num!=max_num && now_num>1 )
						p = 0;
				}
				else
				{
					arg = "点";
					p = prop[data]+v*3;
					if( now_num>=max_num/2 && now_num!=max_num && now_num>1 )
						p = p/2;
				}
				if( p!=0 )
					str+= sprintf("  %s"HIR"%s"NOR HIY"%d%s"NOR"\n",c_apply(data),p>=0?"+":"-",p>=0?p:-p,arg);
			}
			return str;
		}					
		else	return "";
	}	
	str = MUDLIB_NAME+"目前可选的套装有"+sizeof(strs)+"个：\n";
	reset_eval_cost();	
	for(i=0;i<sizeof(strs);i++)
	{
		name = strs[i];
		title = mods[name]["title"];
		str+= sprintf("  %18s",name+"之"+COLOR_D->clean_color(title));
		
		datas = mods[name]["need"];
		tmp = "";
		for(k=0;k<sizeof(datas);k++)
		{
			tmp+= sprintf("%s",(("/cmds/std/look.c")->armor_type(datas[k]))[0..1]);
			if( k<sizeof(datas)-1 )
				tmp+= "/";
		}
		str+= sprintf(" 需：%18-s",tmp);
		prop = mods[name]["prop"];
		datas = keys(prop);
		tmp = "";	
		for(k=0;k<sizeof(datas);k++)
		{
			data = datas[k];
			if( member_array(data,keys(("/cmds/std/look.c")->query_euqip_look2()))!=-1 )
				arg = "%";
			else	arg = "";	
			if( prop[data]!=0 )
				tmp+= sprintf("%s"HIR"%s"HIY"%-d%s"NOR,c_apply(data),prop[data]>0?"+":"-",prop[data]>=0?prop[data]:-prop[data],arg);
			if( k<sizeof(datas)-1 )
				tmp+= NOR HIG"/"NOR;
		}
		str+= tmp+"\n";
		str = replace_string(str,COLOR_D->clean_color(title),COLOR_D->replace_color(title,2));
		str = replace_string(str,name,HIC+name+NOR);
	}
	return str;
}	
		