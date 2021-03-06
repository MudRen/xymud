#include <ansi.h>
#include <armor.h>
inherit F_CLEAN_UP;

int have_equip(object who,int v)
{
	object *inv;
	int i;
	if( !who || !living(who) )
		return 1;
	inv = all_inventory(who);
	if( !inv || !arrayp(inv) || sizeof(inv)<1 )
		return 0;
	for(i=0;i<sizeof(inv);i++)
	{
		if( !inv[i]->is_zhaohuan() )
			continue;
		if( inv[i]->query("valid_time")==v )
			return 1;	
	}
	return 0;		
}

mixed create_fabao(object who,string type)
{
	mixed *ar,k;
	int e_time,i,f;
	string temp;
	string e_type,e_name,msg,yin;
	object obj;
	
	if( !who || !living(who) || !type )
		return 0;
	ar = who->query("fabao");
        if( !ar || !arrayp(ar) || sizeof(ar)<1 )
        	return 0;
	//以名称召唤
	if( type!="fabao" && type!="Fabao" )
	{
		f = 0;
		k = 0;
		reset_eval_cost();
		for(i=0;i<sizeof(ar);i++)
		{
			temp = ar[i];
			if( sscanf(temp,"%s_%d_%s",e_type,e_time,e_name)!=3 )
				continue;
			if( e_type!="fabao" && e_type!="Fabao")	
			 	continue;
			if( type!=e_name )
				continue;
			if( have_equip(who,e_time) )
			{
				k = e_name;
				continue;
			}				
			obj = new("/obj/fabao");
			switch (random(3))
       	    		{
               			case 0: msg = HIW "一声" HIR "霹雳" HIW "，闪电划破长空，「$n"HIW"」从天而降，飞入$N" HIW "的手中！\n"NOR;break;
               			case 1: msg = HIR "一道" HIY "长虹" HIR "扫过天空，只见「$n"HIR"」落入了$N" HIR "的掌中！\n" NOR;break;
               			default:msg = HIM "只见「$n"HIM "」呤呤作响，大放异彩，挟云带雾，突现在$N"HIM"的掌中！\n" NOR;break;
               		}
			obj->set("name",e_name);
			obj->set("owner_id",who->query("id"));
			obj->set("valid_time",e_time);
			if( !obj->move(who) )
			{
				tell_object(who,HIR"【系统】你的背包已满或负重不够。"NOR"\n");
				if( obj )
					destruct(obj);
				continue;	
			}			
			if( !obj->restore() )
			{
				destruct(obj);
				continue;
			}
			obj->set_name(obj->query("names"),obj->query("ids"));
			obj->setup();
			obj->set("no_give",1);
			obj->set("no_get",1);
			obj->set("no_put",1);
			obj->set("no_save",1);
			obj->set("no_store",1);
			obj->delete("breaked");
			message_combatd(msg,who,obj);
			if( who->query("env/brief_message") )
				write("你召唤了"+obj->name()+"。\n");
			f++;
		}
		if( f==0 )
		{
			if( k )
				return notify_fail("你已经召唤了"+k+"。\n");
			else	return 0;
		}
		else	return 1;	
	}
	reset_eval_cost();
	f = 0;
	k = 0;
	for(i=0;i<sizeof(ar);i++)
	{
		temp = ar[i];
		if( sscanf(temp,"%s_%d_%s",e_type,e_time,e_name)!=3 )
			continue;
		if( e_type!="fabao" && e_type!="Fabao")	
			continue;
		if( type!=e_type )
			continue;
		if( have_equip(who,e_time) )
		{
			k=e_name;
			continue;
		}			
		obj = new("/obj/fabao");
		switch (random(3))
		{
              		case 0: msg = HIW "一声" HIR "霹雳" HIW "，闪电划破长空，「$n"HIW"」从天而降，飞入$N" HIW "的手中！\n"NOR;break;
               		case 1: msg = HIR "一道" HIY "长虹" HIR "扫过天空，只见「$n"HIR"」落入了$N" HIR "的掌中！\n" NOR;break;
               		default:msg = HIM "只见「$n"HIM "」呤呤作响，大放异彩，挟云带雾，突现在$N"HIM"的掌中！\n" NOR;break;
		}
		obj->set("name",e_name);
		obj->set("owner_id",who->query("id"));
		obj->set("valid_time",e_time);
		if( !obj->move(who) )
		{
			tell_object(who,HIR"【系统】你的背包已满或负重不够。"NOR"\n");
			if( obj )
				destruct(obj);
			continue;	
		}
		if( !obj->restore() )
		{
			destruct(obj);
			continue;
		}
		obj->set_name(obj->query("names"),obj->query("ids"));
		obj->setup();
		obj->set("no_give",1);
		obj->set("no_get",1);
		obj->set("no_put",1);
		obj->set("no_save",1);
		obj->set("no_store",1);
		obj->delete("breaked");
		message_combatd(msg,who,obj);
		if( who->query("env/brief_message") )
			write("你召唤了"+obj->name()+"。\n");
		f++;				
	}
	if( f==0 )
	{
		if( k )
			return notify_fail("你已经召唤了"+k+"。\n");
		else	return 0;
	}
	else	return 1;			        		
}

mixed create_equip(object who,string type)
{
	mixed *ar,k;
	int e_time,i,f;
	string *armor,*weapon,temp;
	string e_type,e_name,msg,yin;
	object obj;
	
	if( !who || !living(who) || !type )
		return 0;
	ar = who->query("euqips");
        if( !ar || !arrayp(ar) || sizeof(ar)<1 )
        {
        	notify_fail("你没有绑定过装备。\n");
        	return create_fabao(who,type);
        }
        armor = ({
		"armor","cloth","hands","kui","neck","pifeng","ring","shield","shoes","waist","wrists",
                "finger","boots","head","surcoat",
	});
	weapon = ({
		"axe","blade","fork","hammer","mace","spear","staff","stick","sword","unarmed","whip",
	});
	//以名称召唤
	if( member_array(type,armor)==-1 && member_array(type,weapon)==-1 && type!="fabao" && type!="Fabao" )
	{
		f = 0;
		k = 0;
		reset_eval_cost();
		for(i=0;i<sizeof(ar);i++)
		{
			temp = ar[i];
			if( sscanf(temp,"%s_%d_%s",e_type,e_time,e_name)!=3 )
				continue;
			if( member_array(e_type,armor)==-1
			 && member_array(e_type,weapon)==-1 )
			 	continue;
			if( type!="all" )
			{	
				if( type=="wuqi" && member_array(e_type,weapon)==-1 )
					continue;
				else if( type=="kuijia" && member_array(e_type,armor)==-1 )
					continue;
				else if( type!=e_name )
					continue;
			}			 	
			if( have_equip(who,e_time) )
			{
				k = e_name;
				continue;
			}				
			if( member_array(e_type,armor)!=-1 )
			{
				obj = new("/obj/armor");
				obj->set("armor_type",e_type);
				if( !who->query("class") )
					yin = "遁甲印";
				else if( who->query("class")=="yaomo" )
					yin = "上古妖印";
				else if( who->query("class")=="bonze" )
					yin = "佛印";
				else	yin = "道印";			
				switch (random(3))
       	    			{
               				case 0: msg = HIY"$N"HIY"手结"+yin+"，「$n"HIY"」从虚空中显出了形状，落在$P手中！\n"NOR;break; 
               				case 1: msg = HIC"$N"HIC"口中喃喃念了几句咒语，只见霞光四射，「$n"HIC"」从天而降，落在了$P手中！\n"NOR;break;
               				default:msg = HIG"只见「$n"HIG"」霞彩四溢，大放异彩，突现在$N"HIG"的掌中！\n" NOR;break;
               			}
			}
			else
			{
				obj = new("/obj/weapon");
				obj->set("skill_type",e_type);
				switch (random(3))
       	    			{
               				case 0: msg = HIW "一声" HIR "霹雳" HIW "，闪电划破长空，「$n"HIW"」从天而降，飞入$N" HIW "的手中！\n"NOR;break;
               				case 1: msg = HIR "一道" HIY "长虹" HIR "扫过天空，只见「$n"HIR"」落入了$N" HIR "的掌中！\n" NOR;break;
               				default:msg = HIM "只见「$n"HIM "」呤呤作响，大放异彩，挟云带雾，突现在$N"HIM"的掌中！\n" NOR;break;
               			}
			}
			obj->set("name",e_name);
			obj->set("owner_id",who->query("id"));
			obj->set("valid_time",e_time);
			if( !obj->move(who) )
			{
				tell_object(who,HIR"【系统】你的背包已满或负重不够。"NOR"\n");
				if( obj )
					destruct(obj);
				continue;	
			}			
			if( !obj->restore() )
			{
				destruct(obj);
				continue;
			}
			obj->set_name(obj->query("names"),obj->query("ids"));
			obj->setup();
			obj->set("no_give",1);
			obj->set("no_get",1);
			obj->set("no_put",1);
			obj->set("no_save",1);
			obj->set("no_store",1);
			obj->delete("breaked");
			message_combatd(msg,who,obj);
			if( who->query("env/brief_message") )
				write("你召唤了"+obj->name()+"。\n");
			f++;
		}
		if( f==0 )
		{
			if( k )
				return notify_fail("你已经召唤了"+k+"。\n");
			else
			{
				notify_fail("你并没有绑定名为"HIC+type+NOR"的装备。\n");
				return create_fabao(who,type);
			}
		}
		else	return 1;	
	}
	reset_eval_cost();
	f = 0;
	k = 0;
	for(i=0;i<sizeof(ar);i++)
	{
		temp = ar[i];
		if( sscanf(temp,"%s_%d_%s",e_type,e_time,e_name)!=3 )
			continue;
		if( member_array(e_type,armor)==-1
		 && member_array(e_type,weapon)==-1 )
			continue;
		if( type!=e_type )
			continue;
		if( have_equip(who,e_time) )
		{
			k=e_name;
			continue;
		}			
		if( member_array(e_type,armor)!=-1 )
		{
			obj = new("/obj/armor");
			obj->set("armor_type",e_type);
			if( !who->query("class") )
				yin = "遁甲印";
			else if( who->query("class")=="yaomo" )
				yin = "上古妖印";
			else if( who->query("class")=="bonze" )
				yin = "佛印";
			else	yin = "道印";			
			switch (random(3))
       	    		{
               			case 0: msg = HIY"$N"HIY"手结"+yin+"，「$n"HIY"」从虚空中显出了形状，落在$P手中！\n"NOR;break; 
               			case 1: msg = HIC"$N"HIC"口中喃喃念了几句咒语，只见霞光四射，「$n"HIC"」从天而降，落在了$P手中！\n"NOR;break;
               			default:msg = HIG"只见「$n"HIG"」霞彩四溢，大放异彩，突现在$N"HIG"的掌中！\n" NOR;break;
               		}
		}
		else
		{
			obj = new("/obj/weapon");
			obj->set("skill_type",e_type);
			switch (random(3))
       	    		{
               			case 0: msg = HIW "一声" HIR "霹雳" HIW "，闪电划破长空，「$n"HIW"」从天而降，飞入$N" HIW "的手中！\n"NOR;break;
               			case 1: msg = HIR "一道" HIY "长虹" HIR "扫过天空，只见「$n"HIR"」落入了$N" HIR "的掌中！\n" NOR;break;
               			default:msg = HIM "只见「$n"HIM "」呤呤作响，大放异彩，挟云带雾，突现在$N"HIM "的掌中！\n" NOR;break;
               		}
		}
		obj->set("name",e_name);
		obj->set("owner_id",who->query("id"));
		obj->set("valid_time",e_time);
		if( !obj->move(who) )
		{
			tell_object(who,HIR"【系统】你的背包已满或负重不够。"NOR"\n");
			if( obj )
				destruct(obj);
			continue;	
		}
		if( !obj->restore() )
		{
			destruct(obj);
			continue;
		}
		obj->set_name(obj->query("names"),obj->query("ids"));
		obj->setup();
		obj->set("no_give",1);
		obj->set("no_get",1);
		obj->set("no_put",1);
		obj->set("no_save",1);
		obj->set("no_store",1);
		obj->delete("breaked");
		message_combatd(msg,who,obj);
		if( who->query("env/brief_message") )
			write("你召唤了"+obj->name()+"。\n");
		f++;				
	}
	if( f==0 )
	{
		if( k )
			return notify_fail("你已经召唤了"+k+"。\n");
		else	
		{
			notify_fail("你并没有绑定名为"HIY+type+NOR"的装备。\n");
			return create_fabao(who,type);
		}
	}
	else	return 1;			        		
}

int main(object me, string arg)
{
	mixed *ar;
	string e_type,*names,e_name,type,*types,temp,arg2;
	string *armor,*weapon;
	int e_time,i,f,k,j,err=0,just;
	mapping prop;
	
	if( me->is_busy() )
        	return notify_fail("你现在忙着呢。\n");
        ar = me->query("euqips");
        if( !ar || !arrayp(ar) || sizeof(ar)<1 )
        {
        	just = 1;
        	ar = me->query("fabao");
        	if( !ar || !arrayp(ar) || sizeof(ar)<1 )
        		return notify_fail("你没有绑定过装备。\n");
        }
	armor = ({
		"armor","cloth","hands","kui","neck","pifeng","ring","shield","shoes","waist","wrists",
                "finger","boots","head","surcoat",
	});
	weapon = ({
		"axe","blade","fork","hammer","mace","spear","staff","stick","sword","unarmed","whip",
	});        	
        if( !arg )
        {
        	prop = ([]);
        	f = 0;
        	reset_eval_cost();
        	if( !just )
        	{
        		for(i=0;i<sizeof(ar);i++)
			{
				temp = ar[i];
				if( sscanf(temp,"%s_%d_%s",e_type,e_time,e_name)!=3 )
					continue;
				if( file_size(sprintf("/data/equip/%c/%s/%s", me->query("id")[0],me->query("id"),temp)+ __SAVE_EXTENSION__)<1 )
				{
					ar-= ({temp});
					err++;
					log_file("mod",ctime(time())+" "+me->query("id")+" del err MOD:"+temp+"\n");
					continue;
				}	
                        	if( e_type=="finger" )  e_type="ring";
                        	if( e_type=="boots" )  e_type="shoes";
				f++;	
				if( undefinedp(prop[e_type]) )
					prop[e_type] = ({e_name});
				else	prop[e_type]+= ({e_name});	
       	 		}
       	 		if( f==0 )
       	 			return notify_fail("你并没有绑定名为"+type+"的武器或防具。\n");
       	 		types = keys(prop);
	       	 	types = sort_array( types, (: strcmp :) );
       		 	arg = "你目前绑定的装备有：\n";
       	 		arg+= HIC" □"NOR"防具\n";
	       	 	arg2 = HIC" □"NOR"武器\n"; 
       		 	f = k = 0;
       	 		for(i=0;i<sizeof(types);i++)
       	 		{
       	 			type = types[i];
       	 			names = prop[type];
       	 			if( member_array(type,armor)!=-1 )
       	 			{
	       	 			arg+= "    "+("/cmds/std/look.c")->armor_type(type)+"("+type+")\n";
       		 			arg+= "        ";
       	 				f++;
       	 				for(j=0;j<sizeof(names);j++)
       	 				{
       	 					arg+= names[j];
	       	 				if( f!=0 && f%4==0 && f<j )
       		 					arg+= "\n        ";
       	 					else	arg+= "  ";	
       	 				}
       	 				arg+= "\n";	
       	 			}
	       	 		else
       		 		{
       	 				arg2+= "    "+("/cmds/std/look.c")->weapon_type(type)+"("+type+")\n";
       	 				arg2+= "        ";
       	 				k++;
	       	 			for(j=0;j<sizeof(names);j++)
       		 			{
       	 					arg2+= names[j];
       	 					if( k!=0 && k%4==0 && k<j)
       	 						arg2+= "\n        ";
       	 					else	arg2+= "  ";	
       	 				}
       	 				arg2+= "\n";	
       	 			}
       	 		}
       	 		
       	 		if( err>0 )
       	 		{
       	 			ar-= ({0});
	       	 		if( sizeof(ar)<1 )
       		 			me->delete("euqips");
       	 			else	me->set("euqips",ar);
       	 			me->save();	
       	 		}	
//       	 	me->start_busy(1);
	       	 	me->start_more(arg+arg2);
	       	}
		//法宝       	 	
       	 	prop = ([]);
        	f = 0;
        	err = 0;
		arg = HIC" □"NOR"法宝(Fabao)\n";
        	if( arrayp(ar = me->query("fabao"))
        	 && sizeof(ar)>0 )
		{        	 
        		reset_eval_cost();
	        	for(i=0;i<sizeof(ar);i++)
			{
				temp = ar[i];
				if( sscanf(temp,"Fabao_%d_%s",e_time,e_name)!=2 )
					continue;
				if( file_size(sprintf("/data/equip/%c/%s/%s", me->query("id")[0],me->query("id"),temp)+ __SAVE_EXTENSION__)<1 )
				{
					ar-= ({temp});
					err++;
					log_file("mod",ctime(time())+" "+me->query("id")+" del err MOD:"+temp+"\n");
					continue;
				}	
				f++;
				arg+= "        "+e_name;
				if( i!=0 && i%4==0 )
					arg+= "\n        ";
				else	arg+= "  ";	
			}
			if( err>0 )
       	 		{
       	 			ar-= ({0});
       	 			if( sizeof(ar)<1 )
       	 				me->delete("fabao");
       	 			else	me->set("fabao",ar);
       	 			me->save();	
       	 		}
       	 		arg+= "\n";
       	 		me->start_more(arg);	
       	 	}
       	 	write("你可以使用"HIR" zhaohuan <装备类型> "NOR"来召唤绑定的装备，"HIG"示例：zhaohuan armor"NOR"。\n");
       	 	write("还可以使用"HIR" zhaohuan <装备名称> "NOR"来召唤绑定的装备，"HIG"示例：zhaohuan 嫦娥之七劫"NOR"。\n");
       	 	return 1;	
	}
	if( environment(me)->query("killer") || environment(me)->query("no_zhaohuan") )
        	return notify_fail("这个地方，你感觉有点难以召唤武器和防具。\n");
        if( arg=="ring" )
        	arg = "finger";
        if( arg=="shoes" )
        	arg = "boots";		
        if( arg=="kui" )
                arg = "head";          
        if( arg=="pifeng" )
                arg = "surcoat";
	if( !create_equip(me,arg) )
		return 0;
        else
        {
//        	me->start_busy(1);
        	return 1;
        }	
	write("ok.\n");
	return 1;
}

int help(object me)
{
write(@HELP
指令格式： zhaohuan 	       - 查看你绑定的所有装备
	   zhaohuan [中文名]   - 召唤你绑定的名称为指定名的所有装备
	   zhaohuan [装备类型] - 召唤你绑定的类型为指定类型的所有装备
	   zhaohuan [all]      - 召唤你绑定的所有装备	

这个指令让你可以召唤回你专属的装备

HELP
        );
return 1;
}

