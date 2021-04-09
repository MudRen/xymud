inherit NPC;

void create()
{
        set_name("范青屏", ({"fan qingping", "fan"}));
        set_level(30);
        set("age", 72);
        set("gender", "男性");
        set("long",
"范老拳师壮年时也是响当当的英雄，现在虽老了，手脚利落却不输当年．\n");
        set("title", "拳盖三省");
        set("attitude", "friendly");
        set("max_kee", 800);
        set("max_sen", 700);
        set("combat_exp", 100000);
  set("daoxing", 50000);

        set("shen_type", 1);
        set("max_force", 300);
        set("force", 300);
        set("force_factor", 15);
        set_skill("unarmed", 300);
        set_skill("changquan", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        map_skill("unarmed", "changquan");
        set("chat_chance",1);
        set("chat_msg", ({
        "范青屏叹道：腿脚不利落了，也没人去给我提笼小二的包子来。\n",
}));
        setup();
        carry_object(0,"cloth",random(2))->wear();        
	carry_object(0,"shoes",random(2))->wear(); 
	carry_object(0,"pifeng",random(2))->wear();        	       
	carry_object(0,"unarmed",random(2))->wield(); 
        carry_object("/d/obj/book/quanjing");
}

int accept_object(object who,object ob)
{
        if( ob->query("id")=="zhurou bao" )
        {
                command("say 嘿嘿，老二这包子是越做越小了。\n");
                command("say 不过还是要谢谢你呀！\n");
                command("give jing to " + who->query("id"));
                return 1;
        }

/*
        if( ob->query("money_id") && ob->value()>=3000 ) 
        {
                object room,npc,*old;
                int i;
        //清除以前残留的房间和NPC
                old = children("/d/city/npc/wg_fighter");
                for(i=0;i<sizeof(old);i++)
                        if( old[i] && old[i]->query("owner_id")==who->query("id") )
                                destruct(old[i]);
                old = children("/d/city/fight_room");
                for(i=0;i<sizeof(old);i++)
                        if( old[i] && old[i]->query("owner_id")==who->query("id") )
                                destruct(old[i]);
        //清理完毕        
                room = clone_object("/d/city/fight_room");
                if( !room )  return 0;
                room->set("owner",who);
                room->set("owner_id",who->query("id"));
                room->set("owner_name",who->query("name"));
                room->set("long",sprintf(room->query("long")+"\n",who->name()) );
                npc = clone_object("/d/city/npc/wg_fighter");
                if( !npc || !npc->move(room) )
                {
                        destruct(room);
                        return 0;
                }
                npc->set("owner",who);
                npc->set("owner_id",who);
                if( who->move(room) )
                {
                        message_vision("$N拱手将$n让进了里间。\n",this_object(),who);
                        return 1;
                }
                destruct(npc);
                destruct(room);
                return 0;
        }
*/
        return 0;
}
