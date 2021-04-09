inherit ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_put", "put");
}

varargs string query_yao(object obj)
{
	string file;
	if( obj )
		file = base_name(obj);
	else	file = query("drug_file");	
	switch(file)
        {
        	case "/d/obj/drug/jinchuang"  : return "金创药";
        	case "/d/obj/drug/jinchuang2" : return "金创药(中)";
        	case "/d/obj/drug/jinchuang3" : return "金创药(大)";
        	default : return "";
        }        
}

void create()
{
        set_name("金创药瓶", ({"jinchuang yao", "yao", "jinchuang","yaoping","yao ping","ping"}));
	set("unit","瓶");
        set("long", "这是一个放金创药的瓶子，可以直接吃(eat)里面的金创药。\n");
        set("value", 10000);
        set("changed",1);
        set("no_sell",1);
        set("drug_file","/d/obj/drug/jinchuang");
        set("drug_type", "良药");
        set("num",1);
        setup();
}

int do_eat(string arg)
{
	int drug;
        if( !arg || !id(arg) )
                return 0;
        if (this_player()->query("eff_kee") == this_player()->query_maxkee())
        	return err_msg("你现在不需要用金创药。\n");
        if( query("num")<=0 )
                return notify_fail("瓶子已经空了。\n");
        switch(query("drug_file"))
        {
        	case "/d/obj/drug/jinchuang"  : drug=100;break;
        	case "/d/obj/drug/jinchuang2" : drug=500;break;
        	case "/d/obj/drug/jinchuang3" : drug=1000;break;
        	default : return notify_fail(name()+"里不知放了什么，但肯定不是金创药。\n");
        }
        this_player()->receive_curing("kee", drug);
        message_vision("$N从瓶中掏出一粒"+query_yao()+"吃下，气色看起来好多了。\n",this_player());
        add("num",-1);
        if( query("num")<=0 )
                tell_object(this_player(),"瓶子中的"+query_yao()+"已经吃光了。\n");
        return 1;
}

string long()
{
        string arg,str = ::long();
        if( query("num")<=0 )
                str+= "瓶子中的药已经吃光了。\n";
        else    str+= "瓶子里还有"+chinese_number(query("num"))+"粒"+query_yao()+"。\n";
        return str;
}

int do_put(string arg)
{
        int v,now;
        string id,name;
        object box,yao,obj,me = this_player();
        
        if( !arg || !present(this_object(),me) )
                return 0;
        if( sscanf(arg,"%s in %s",id,arg)!=2 )
                return 0;
        if( sscanf(id,"%d %s",v,id)!=2 )
                v = 0;
        if( v<0 )
                return 0;
        box = present(arg,me);
        if( !box || box!=this_object() )        
                return 0;
        yao = present(id,me);
        if( yao==this_object() )
        	yao = present(id+" 2",me);
        if( !yao )
                return 0;
	if( !stringp(arg=base_name(yao)) )
		return 0;
	
	name = query_yao(yao);
	if( name=="" )	
		return notify_fail("瓶子里只能放金创药。\n");
	if( v==0 )
                v = yao->query_amount();

	now = query("num");
	if( query("drug_file") )
	{
		if( arg!=query("drug_file") )
		{
			if( now>0 )
			{
				obj = new(query("drug_file"));
				obj->set_amount(now);
				if( !obj->move(me) )
					obj->move(environment(me));
				message_vision("$N从$n拿出了一些"+query_yao(obj)+"。\n",me,this_object());
			}
			set("drug_file",arg);	
			set("num",v);
		}
		else
		{
			if( v+query("num")>=100000 )
        			return err_msg("瓶子放不下了。\n");
			add("num",v);
		}
	}
	else
	{
		set("drug_file",arg);
		set("num",v);		
	}
	message_vision("$N将一些"+query_yao(yao)+"放进了$n中。\n",me,this_object());
        if( v==yao->query_amount() )
                destruct(yao);
        else    yao->add_amount(-v);
        return 1;
} 