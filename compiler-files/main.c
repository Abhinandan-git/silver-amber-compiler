#include "main.h"

int main()
{
	if (preprocessor("file.ffo", "raw_code.ffo") == INCOMPLETE)
	{
		return INCOMPLETE;
	}

	return COMPLETE;
}