inherit F_VENDOR_SALE;

string heal_me(object me);

void create()
{
        set_name("医馆伙计", ({"huo ji","boss"}));
        set("gender", "男性");
        set("age", 17);
        set("vendor_goods", ([
                "yao": "/d/obj/drug/jinchuang",
                "dan": "/d/obj/drug/hunyuandan",
        ]) );
        setup();
        carry_object(0,"cloth",1)->wear();
}
