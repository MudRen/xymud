int atoi(string str)
{
        int v;
        if( !stringp(str) || !sscanf(str, "%d", v) ) 
                return 0;
        return v;
}

int last_num(int v)
{
        int i;
        string str;
        if( v<=0 )
                return 0;
        str = sprintf("%d",v);
        i = strlen(str);
        str = sprintf("%c",str[i-1]);
        sscanf(str,"%d",v);
        return v;
}

nomask varargs int Int_com(int ap,int dp,int v)
{
        return 1;
}
