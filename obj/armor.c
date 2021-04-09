#include <ansi.h>
#include <armor.h>
#include <dbase.h>
inherit EQUIP; 
inherit F_SAVE;

string query_name() { return "特殊防具(+技能)"; }

string query_save_file()
{
	string name;
	if( !query("owner_id") || !stringp(query("owner_id")) )
        	return 0;
        name = this_object()->name();
        if( !name || !stringp(name) )
        	return 0;
        name = COLOR_D->clean_color(name);	
	return sprintf("/data/equip/%c/%s/%s_%d_%s", query("owner_id")[0],query("owner_id"),query("armor_type"),query("valid_time"),name);
}

void leave()
{
	remove_call_out("leave");
	write("\n"+this_object()->name()+HIY"化作一道金光冲天而去。\n\n"NOR);
	destruct(this_object());
}

void _leave()
{
	call_out("leave",2+random(5));
}               

void check_owner()
{
	object env = environment();
	if( env )
	{
	    	if( !userp(env) )
                	_leave();
            	if( query("owner_id") && query("owner_id")!=env->query("id") )
                	_leave();                       
	}         
}

int err_msgs(string arg)
{
	write(arg);
	return 0;
}

int to_save()
{
	int t;
	string type,name;
	mixed *ar;
	object me = environment();
	if( !me || !query("owner_id") 
	 || me->query("id")!=query("owner_id") )
		return err_msgs("这不是你的。\n");
	if( me->is_busy() )
		return err_msgs("你正忙着。\n");
	if( query("no_save") )
		return err_msgs("这个物品不能绑定。\n");
	if( !type=query("armor_type") )
		return err_msgs("未知的防具类型。\n");		
	if( query("equipped") )
		return err_msgs("你必须先将"+this_object()->query("name")+"卸下。\n");
	if( (me->query("potential")-me->query("learned_points"))<500 )   
		return err_msgs("你的潜能不够,无法保存法宝。\n");
	me->start_busy(1); 		
	set("valid_time",time());
	t = query("valid_time");
	ar = me->query("euqips");
	if( !ar || !arrayp(ar) || sizeof(ar)<1 )
		ar = ({});
	ar-= ({0});	
	set("no_give",1);
	set("no_save",1);
	delete("changed");
	if( this_object()->save() )
	{
        	me->add("potential",-500);
        	name = this_object()->name();
        	if( !name || !stringp(name) )
        		name = "无名";
        	name = COLOR_D->clean_color(name);
        	ar+= ({type+"_"+t+"_"+name});
		me->set("euqips",ar);
		me->save(1);
		tell_object(me,HIY"【系统】"+this_object()->name()+HIY"绑定成功，如果消失，你可以通过 zhaohuan 命令来重新获得。"NOR"\n");
        	return 1;
	}
	return 0;
}

int do_dest(string arg)
{
	mixed *ar;
	string type;
	object me = this_player();
	if( !arg || !id(arg) )
        	return 0;
	if( me!=environment() )
        	return 0;  
	if( !query("owner_id") || !query("valid_time") )
        	return 0;
	if( !query("armor_type") )
		return err_msg(name()+"防具类型缺失。\n");
	type = sprintf("%s_%d_%s",query("armor_type"),query("valid_time"),this_object()->name());
	type = COLOR_D->clean_color(type);
	if( !arrayp(ar=me->query("euqips"))
	 || sizeof(ar)<1 
	 || member_array(type,ar)==-1 )
		return err_msg(name()+"不是你的绑定装备。\n");	 
	if( query("owner_id")
  	 && me->query("id")!=query("owner_id") )
        	return err_msg(name()+"是"+query("owner_id")+"的专属防具。\n");
	if( (me->query("potential")-me->query("learned_points"))<500 )   
        	return err_msg("你的潜能不够,无法注销法宝。\n");
        seteuid(getuid());	
	if( !rm(query_save_file()+ __SAVE_EXTENSION__) )
        	return err_msg("注销失败。\n");
	ar-= ({type});
	ar-= ({0});	
	me->add("potential",-500);
	write("注销成功。\n");
	if( sizeof(ar)>0 )
		me->set("euqips",ar);
	else	me->delete("euqips");
	me->save(1);
	message_vision("$N手中的$n轰的一声炸成了碎片。。。。\n",me,this_object());
	destruct(this_object());
	return 1;
}

void init()
{
	check_owner();
        add_action("do_dest",({"destruct","zhuxiao"}) );
}

void create()
{
	set_name("◆防具",({"fang ju"}));
	set("unit","件");
}

string short()
{
	int v;
	string str,temp;
	v = this_object()->query("sheng_level");
	switch(v)
	{
		case 0 : temp = HIR+BLK"下品"NOR;break;
		case 1 : temp = CYN"中品"NOR;break;
		case 2 : temp = WHT"上品"NOR;break;
		default : temp = HIW" 仙品"NOR;break;
	}
	str = query("shorts");
	if( str && stringp(str) )
	{
		str = temp+str;
		return str;
	}
	return ::short();	
}

int is_zhaohuan(){ return 1; }       

//增加特别效果
varargs void level_up2(object who)
{
	mapping prop;
	string *app;
	int i,p;
	prop = ("/d/obj/narmor/newcloth.c")->equip_apply(this_object());
	if( !prop || !mapp(prop) || sizeof(prop)<1 )
		return;
	app = keys(prop);
	if( !app || !arrayp(app) || sizeof(app)<1 )
		return;
	for(i=0;i<sizeof(app);i++)
	{
		p = random(10)/8;
		if( p>0 )
			this_object()->add("armor_prop/"+app[i],p);
	}		
}       

int level_up()
{
	mapping prop;
	string *app;
	int i,p;
	prop = ("/d/obj/narmor/newcloth.c")->equip_base(this_object());
	if( !prop || !mapp(prop) || sizeof(prop)<1 )
		return 0;
	app = keys(prop);
	if( !app || !arrayp(app) || sizeof(app)<1 )
		return 0;
	for(i=0;i<sizeof(app);i++)
	{
		p = prop[app[i]];
		p/= 5;
		if( p<1 ) p = 1;
		p = p+random(p/2);
		this_object()->add("armor_prop/"+app[i],p);
	}		
	return 1;
}

int restore()
{
	if( ::restore() )
	{
		set_name(query("name"),query("ids"));
		return 1;
	}
	return 0;
}

string name()
{
	string cls,name = ::name();
	if( query("armor_title") )
		name = query("armor_title")+"之"+name;
	if( query("armor_color") )
	{
		name = query("armor_color")+name;	
		name = COLOR_D->replace_color(name,1);
		if( query("armor_color")=="HIM" )
		{
			if( query("level")<40 )
				name = HIM"(鬼)"+name;
			else if( !stringp(cls=query("class")) )
				name = HIM"(灵)"+name;
			else
			{
				switch(cls)
				{
					case "shen" : 
					case "dragon" :
					case "fighter" :
					case "xian" : name = HIM"(仙)"+name;break;
					case "youling" :
					case "ghost" : name = HIM"(鬼)"+name;break;
					case "seng"  :
					case "bonze" : name = HIM"(佛)"+name;break;
					case "taoist": name = HIM"(道)"+name;break;
					case "scholar" : name = HIM"(儒)"+name;break;
					case "dancer" : name = HIM"(魅)"+name;break;
					case "yaomo" : name = HIM"(妖)"+name;break;
					case "tianmo" : name = HIM"(魔)"+name;break;
					default : name = HIM"(灵)"+name;break;
				}
			}	
		}
	}
	return name;
}
