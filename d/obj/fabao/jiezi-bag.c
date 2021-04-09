#include <ansi.h>
inherit ITEM; 
inherit F_SAVE;

private nosave string obj_owner;
mapping Gold=([]);
mapping Obj=([]);
nomask void self_destroy();

void create()
{
	set_name(HIG"芥子袋"NOR, ({"jiezi dai","bag","dai"}) );
	set_weight(1000);
	set("no_get",1);
	set("no_sell",1);
	set("no_drop",1);
	set("no_give",1);
	if( clonep() )
        	set_default_object(__FILE__);
	else 
	{
        	set("unit", "个");
        	set("long",@LONG
此乃修真法宝，乃从佛门“须弥藏芥子”的意境中演化而来。其大小视使用人的能力而定。 
	功能命令：
		  放入货币	cunru <数量> <货币类型>
		  拿出货币	quchu <数量> <货币类型>
		  兑换黄金点	dui
		  放入物品	fang   <数量> <物品名称>
		  拿出物品	qu    <数量> <物品名称>
LONG);
	}
	setup();
}

int query_autoload(){ return 1;}

void self_destroy()
{
  object env=environment();

  if(env) {
    if(env->is_character()) { // npc or player
      tell_object(env,"天上忽然传来一声断喝：还我"+
        this_object()->query("name")+"来！\n");
      tell_object(env,"只见"+this_object()->query("name")
        +"凌空而去，霎时间不见了踪影。\n");  
    } else {
      tell_object(env,this_object()->query("name")+
        "钻进地里，霎时间不见了踪影。\n");
    }
  }
  
  destruct(this_object());
}

string query_save_file()
{
        if( !obj_owner )
                return 0;
        return sprintf("/data/bag/%c/%s", obj_owner[0],obj_owner);
}

void check_owner()
{
  	object env=environment();

  	if(!clonep()) return;

  	if(!env) 
  	{
    		call_out("self_destroy",1);
    		return;
  	}
    
  //for room or other containers.  
  	if(!env->is_character()) 
  	{
    		if(obj_owner) call_out("self_destroy",5+random(5));
    		return;
  	}  
  
  //for npc.
  	if(!userp(env)) 
  	{
    		if(obj_owner)
      			call_out("self_destroy",5+random(5));
    		return; 
    //allow NPC to carry it if no one has own it.
  	}  
     
  //following is for user.   
  	if(!obj_owner)
    		obj_owner=env->query("id");
  	else 
  	{
    		if(obj_owner!=env->query("id"))
      			call_out("self_destroy",2+random(5));
    		else	remove_call_out("self_destroy");  
      //one can still pick it up if loses it for a short while.
  	}
}

void init()
{
	check_owner();
	if( restore() )
	{
		add_action("do_cunru","cunru");
		add_action("do_cun","fang");
		add_action("do_quchu","quchu");
		add_action("do_qu","qu");
		add_action("do_dui","dui");
	}
}

int do_dui()
{
	int num;
	object me = this_player();
	if( me->query("id")!=obj_owner )
		return 0;
	if( me!=environment() )
		return 0;
	if( !undefinedp(Gold["gold"]) )
	{
		if( Gold["gold"]>50000000 )
		{
			write("你目前没有兑换的必要。\n");
			return 1;
		}
	}
	if( undefinedp(Gold["point"]) )
	{
		write("你的黄金点不够。\n");
		return 1;
	}
	if( !undefinedp(Gold["gold"]) )
		num = Gold["gold"];
	else	num = 0;
	num+= 100000000;
	Gold["gold"] = num;
	Gold["point"]-= 1;
	write("你兑换了一个黄金点，在下次存放时，如果黄金数量达到一亿，将自动兑换成黄金点。\n");
	save();
	return 1;
}	
		

void update_g()
{
	int x,y,z;
	if( !undefinedp(Gold["coin"]) )
	{
		if( x>100 )
		{
			y = x%100;
			z = x/100;
			Gold["coin"] = y;
			Gold["silver"]+= z;		
		} 
	}
	
	if( !undefinedp(Gold["silver"]) )
	{
		x = Gold["silver"];
		if( x>100 )
		{
			y = x%100;
			z = x/100;
			Gold["silver"] = y;
			Gold["gold"]+= z;		
		} 
	}
	if( !undefinedp(Gold["gold"]) )
	{
		x = Gold["gold"];
		y = x-100000000;
		if( y>0 )
		{
			if( !undefinedp(Gold["point"]) )
				z = Gold["point"];
			else	z = 0;	
			z+= 1;
			Gold["point"] = z;
			Gold["gold"] = y;		
		}
	}
}	

int do_cunru(string arg)
{
	int old,num;
	string type;
	object ob,me = this_player();
	if( me->query("id")!=obj_owner )
		return 0;
	if( !arg || me!=environment() )
		return 0;
	if( sscanf(arg,"%d %s",num,type)!=2 )
		return 0;
	if( type!="gold" && type!="silver" && type!="coin" )
	{
		write("只能放入gold/silver/coin。\n");
		return 1;
	}
	if( num<=0 )
	{
		write("你要放多少"+type+"？\n");
		return 1;
	}
	ob = present(type,me);
	if( !ob || !ob->query("money_id") )
	{
		write("你身上没有"+type+"。\n");
		return 1;
	}
	if( ob->query_amount()<num )
	{
		write("你身上没有这么多的"+type+"。\n");
		return 1;
	}
	
	write("你将"+chinese_number(num)+ob->query("base_unit")+ob->query("name")+"放入"+query("name")+"中。\n");
	if( num<ob->query_amount() )
		ob->add_amount(-num);
	else	destruct(ob);	
	
	if( !undefinedp(Gold[type]) )
		old = Gold[type];
	else 	old = 0;
	num+= old;
	Gold[type] = num;
	update_g();
	save();
	return 1;
}

int do_quchu(string arg)
{
	int old,num;
	string type;
	object ob,me = this_player();
	
	if( me->query("id")!=obj_owner )
		return 0;
	if( !arg || me!=environment() )
		return 0;
	if( sscanf(arg,"%d %s",num,type)!=2 )
		return 0;
	if( type!="gold" && type!="silver" && type!="coin" )
	{
		write("能拿出的货币只能是gold/silver/coin。\n");
		return 1;
	}
	if( num<=0 )
	{
		write("你要拿多少"+type+"？\n");
		return 1;
	}
	if( undefinedp(Gold[type]) )
	{
		write(query("name")+"中并没有"+type+"。\n");
		return 1;
	}
	old = Gold[type];
	if( old<=0 )
	{
		write(query("name")+"中并没有"+type+"。\n");
		return 1;
	}
	if( old<num )
	{
		write(query("name")+"中只有"+old+type+"。\n");
		return 1;
	}
	old = old-num;
	Gold[type] = old;
	ob = new("/obj/money/"+type);
	ob->set_amount(num);
	write("你从"+query("name")+"中取出"+ob->short()+"。\n");	
	if( !ob->move(me) )
		ob->move(environment(me));
	save();		
	return 1;
}

//存特殊物品
int do_cun(string arg)
{
	int num,max;
	string file,name,id;
	mixed *tmp;
	object ob,me = this_player();
	if( me->query("id")!=obj_owner )
		return 0;
	if( !arg || me!=environment() )
		return 0;
	if( sscanf(arg,"%d %s",num,arg)!=2 )
		num = 1;
	if( num<=0 )
	{
		write("你要放多少"+arg+"？\n");		
		return 1;
	}	
		
	ob = present(arg,me);
	if( !ob )
	{
		write("你身上没有"+arg+"。\n");
		return 1;
	}
	if( !ob->in_jiezi() )
	{
		write(ob->query("name")+"不能放入"+query("name")+"中去。\n");
		return 1;
	}
	
	if( ob->query_amount()<1 )
		max = 1;
	else	max = ob->query_amount();
	
	if( num>max )
	{
		write("你身上没有这么多的"+ob->query("name")+"。\n");
		return 1;
	}
	
	name = ob->query("name");
	name = COLOR_D->clean_color(name);
	id = ob->query("id");
	write("你将"+chinese_number(num)+(ob->query("base_unit")?ob->query("base_unit"):ob->query("unit"))+name+"放进了"+query("name")+"中。\n");
	
	file = base_name(ob);
	if( undefinedp(Obj[file]) )
		Obj[file] = ({name,id,num});
	else
	{
		tmp = Obj[file];
		tmp = ({tmp[0],tmp[1],tmp[2]+num});
		Obj[file] = tmp;
	}		
	save();
	if( num<max 
	 && ob->query_amount()>0 )
		ob->add_amount(-num);
	else	destruct(ob);
	return 1;
}

string long()
{
	int i;
	mixed *tmp;
	string str,*msg,file;
	object me = this_player();		 
	str = ::long();		
	if( me->query("id")!=obj_owner )
		return str;
	if( me!=environment() )
		return str;
	if( !undefinedp(Gold["point"]) )
		str+= HIC"\t黄金点："HIR+Gold["point"]+"\n"NOR;
	if( !undefinedp(Gold["gold"]) )
		str+= HIC"\t黄  金："HIR+Gold["gold"]+"\n"NOR;
	if( !undefinedp(Gold["silver"]) )
		str+= HIC"\t白  银："HIR+Gold["silver"]+"\n"NOR;
	if( !undefinedp(Gold["coin"]) )
		str+= HIC"\t文  钱："HIR+Gold["coin"]+"\n"NOR;
	str+= " (注：一点黄金点兑换一亿两黄金)\n\n";
	msg = keys(Obj);
	if( msg )
	{
		for(i=0;i<sizeof(msg);i++)
		{
			file = msg[i];
			if( !file )
				continue;
			tmp = Obj[file];
			if( !tmp ) 
				continue;				
			str+= sprintf("\t"HIG"%50-s 数量：%-20d\n",tmp[0]+"("+capitalize(tmp[1])+")",tmp[2]);
		}
	}
	return str;
}	
		
int do_qu(string arg)
{
	int i,flag;
	mixed *tmp,*msg;
	int num,max;
	string file,name,id;
	object ob,me = this_player();
	
	if( me->query("id")!=obj_owner )
		return 0;
	if( me!=environment() )
		return 0;
	if( !arg || sscanf(arg,"%d %s",num,arg)!=2 )
		return 0;
	msg = keys(Obj);
	if( !msg )
	{
		write("芥子袋中没有存放物品。\n");
		return 1;
	}
	flag = 0;
	for(i=0;i<sizeof(msg);i++)
	{
		tmp = Obj[msg[i]];
		if( !tmp )
			continue;
		if( arg==tmp[1] )
		{
			flag = 1;
			file = msg[i];
			max = tmp[2];
			name = tmp[0];
			id = tmp[1];
			break;
		}
		else	continue;
	}
	if( !flag )
	{
		write("芥子袋中没有"+arg+"。\n");
		return 1;
	}
	
	if( num>max )
	{
		write("芥子袋中没有这么多的"+name+"。\n");
		return 1;
	}
	
	ob = new(file);
	if( !ob )
	{
		write(name+"读取错误，请联系巫师。\n");
		return 1;
	}
	if( !ob->query_amount()
	 && num>1 )
	{
		destruct(ob);
		write(name+"每次只能取一样。\n");
		return 1;
	}
	
	write("你从芥子袋中取出"+chinese_number(num)+(ob->query("base_unit")?ob->query("base_unit"):ob->query("unit"))+name+"。\n");
	max = max-num;
	map_delete(Obj,file);
	if( max>0 )
		Obj[file] = ({name,id,max});
	save();			
	ob->set_amount(num);
	ob->move(me);
	return 1;
}