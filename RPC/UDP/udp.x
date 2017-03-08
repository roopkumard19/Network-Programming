struct input
{

char arg1[2100];
};

struct output
{

char res1[2100];
};


program FILE_SERVER
{
version FILE_VERS
{
output FILESERVERPROC(input)=1;
}=1;
}=0x12345678;

