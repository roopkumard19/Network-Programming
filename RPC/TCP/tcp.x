struct input
{

char arg1[2024];
};

struct output
{

char res1[2024];
};


program FILE_SERVER
{
version FILE_VERS
{
output FILESERVERPROC(input)=1;
}=1;
}=0x12345678;

