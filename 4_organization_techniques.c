#include <iostream>
#include <cstring>
using namespace std;
struct Directory
{
char dname[10];
char fname[10][10];
int fcnt;
};
int main()
{
int i, ch;
char f[30];
Directory dir;
dir.fcnt = 0;
cout << "Enter name of directory -- ";
cin >> dir.dname;
while (true)
{
cout << "\n\n 1. Create File\t2. Delete File\t3. Search File"
<< "\n 4. Display Files\t5. Exit\nEnter your choice -- ";
cin >> ch;
switch (ch)
{
case 1:
cout << "\n Enter the name of the file -- ";
cin >> dir.fname[dir.fcnt];
dir.fcnt++;
break;
29
case 2:
cout << "
\n Enter the name of the file -- ";
cin >> f;
for (i = 0; i < dir.fcnt; i++) {
if (strcmp(f, dir.fname[i]) == 0) {
cout << "File " << f << " is deleted";
strcpy(dir.fname[i], dir.fname[dir.fcnt 
- 1]);
break;
}
}
if (i == dir.fcnt)
cout << "File " << f << " not found";
else
dir.fcnt--
;
break;
case 3:
cout << "
\n Enter the name of the file -- ";
cin >> f
;
for (i = 0; i < dir.fcnt; i++) {
if (strcmp(f, dir.fname[i]) == 0) {
cout << "File " << f << " is found";
break;
}
}
if (i == dir.fcnt)
cout << "File " << f << " not found";
break;
case 4:
if (dir.fcnt == 0)
cout << "
\n Directory Empty";
else {
cout << "
\n The Files are -- ";
for (i = 0; i < dir.fcnt; i++)
cout << "
\t" << dir.fname[i];
}
break;
default:
exit(0);
}
}
return 0;
}
