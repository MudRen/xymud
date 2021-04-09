mapping autoload;

void clean_up_autoload(){autoload=0;} 

int is_save(object ob)
{
        string *item=({  //需要保存的物品文件名列表，也可根据需要设置为不保留的物品列表 query("changed")>=1的，保存所有属性，否则只保存文件和数量
//             "/d/obj/newitem/baoshi/baoshi",
                });
        if( !ob ) return 0;
        if( ob->is_character() ) return 0;
        if( !this_object()->visible(ob) )  return 0;
        if( ob->query("armor_type") || ob->query("skill_type") ) return 1;
        if( ob->query("changed") ) return 1;
        if( ob->query_autoload() ) return 1;
        //if( member_array(base_name(ob),item) >= 0) return 1;
        return 0;               
}

int save_autoload()
{
        object *inv;
        int i;

        if( !userp(this_object()) ) return 0;
       	autoload = allocate_mapping(1000); //先预定义为1000的大小
        inv = all_inventory();
        for(i=0; i<sizeof(inv); i++)
        {
		if( !is_save(inv[i])) continue;  //只保存指定的物品   
		autoload[i] = ([
			"file" : base_name(inv[i]),
			"num"  : inv[i]->query_amount(),
			"data" : inv[i]->query_entire_dbase(),
			"name" : inv[i]->query("name"),
			"id"   : inv[i]->parse_command_id_list(),
		]);
	}
	return i;
}

int restore_autoload()
{
        int i,j;
        object ob;
        string file, err,*key;
        mapping data;

        if( !autoload || !mapp(autoload) ) 
        	return 0;
        i=0;
        while(!undefinedp(autoload[i]))
        {
                file = autoload[i]["file"];
                err = catch(ob = new(file));
          	if( err || !ob  ) 
                {
                	CHANNEL_D->do_channel(this_object(),"chat","自动存储物品："+file+" 读取错误。");
                        log_file("autoload", sprintf("Fail to autoload %s of %s, error %s on %s\n",file, this_object()->query("id"), err, ctime(time())));
                        continue;
                }
                if( autoload[i]["num"]>0 )
                	ob->set_amount(file = autoload[i]["num"]);
                ob->set_name(file = autoload[i]["name"],file = autoload[i]["id"]);
                
                data = file = autoload[i]["data"];
		key = keys(data);
		for(j=0;j<sizeof(key);j++)
		{
			if( key[j]=="id" || key[j]=="name" || key[j]=="equipped" )
				continue;
			ob->set(key[j],data[key[j]]);						                
                }
                export_uid(ob);
                if( !ob->move(this_object()) )
                {
                	CHANNEL_D->do_channel(this_object(),"chat","自动存储物品："+file+" 读取错误。");
                        log_file("autoload", sprintf("Fail to move autoload %s of %s, on %s\n",file, this_object()->query("id"), ctime(time())));
                	if( ob )  destruct(ob);
                        continue;
                }
                i++;
        }
 	clean_up_autoload();
 	return i;
}
