#include <stdio.h>
#include <time.h>

#include "test_case.h"
#include "unit_test.h"

#include "string_conversion/kind.h"
#include "string_conversion/type.h"

const unsigned int unit_test_count = 2;
struct unit_test unit_tests[] =
{
	{
		"Kind string conversion",
		init_kind_string_conversion,
		test_kind_string_conversion,
		free_kind_string_conversion
	},
	{
		"Type string conversion",
		init_type_string_conversion,
		test_type_string_conversion,
		free_type_string_conversion
	}
};

const char* report_header = "\\documentclass{article}\n"
                            "\\usepackage{xcolor}\n"
                            "\\definecolor{shadecolor}{RGB}{150,150,150}\n"
                            "\\newcommand{\\mybox}[1]{\\par\\noindent\\colorbox{shadecolor}\n"
                            "{\\parbox{\\dimexpr\\textwidth-2\\fboxsep\\relax}{#1}}}\n";

int
main (void)
{
	unsigned int t_idx;
	unsigned int c_idx;
	int retval;
	FILE* report;

	report = fopen("report.tex", "w");
	fprintf(report, "%s", report_header);
	fprintf(report, "\\begin{document}\n");
	fprintf(report, "\\begin{center}\n");
	fprintf(report, "{\\Huge \\bf libctf unit tests}\\\\\n");

	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	fprintf(report, "%d-%d-%d %d:%d:%d \\\\ \n", tm->tm_year + 1900, tm->tm_mon + 1,
	  tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

	fprintf(report, "\\end{center}\n");

	fprintf(report, "Operating system: ");
	#ifdef __FreeBSD__
		fprintf(report, "FreeBSD %d \\\\\n", __FreeBSD__);
	#endif

	#ifdef __clang__
		fprintf(report, "Compiler: clang %d.%d.%d \\\\\n", __clang_major__, 
		  __clang_minor__, __clang_patchlevel__);	

		fprintf(report, "Endian: ");
		#ifdef __LITTLE_ENDIAN__
			fprintf(report, "little \\\\\n");
		#else
			fprintf(report, "big \\\\\n");
		#endif

		fprintf(report, "{\\tt int} size: %d \\\\\n", __SIZEOF_INT__);

		#ifdef __STDC__
			fprintf(report, "STD C version: %ld \\\\\n", __STDC_VERSION__);
		#endif
	#endif

	fprintf(report, "\\newpage \n");

	for (t_idx = 0; t_idx < unit_test_count; t_idx++)
	{
		printf("  \e[1m%02d) %s\e[0m\n", t_idx, unit_tests[t_idx].name);
		fprintf(report, "\\section*{\\#%d %s}\n", t_idx, unit_tests[t_idx].name);

		struct test_case_head* head = unit_tests[t_idx].init();
		struct test_case* runner = NULL;
		c_idx = 0;

		TAILQ_FOREACH(runner, head, test_cases)
		{
			printf("  %02d.%02d) %s", t_idx, c_idx, runner->description);
			retval = unit_tests[t_idx].test(runner);

			if (retval == _CTF_UNIT_TEST_SUCCESS)
			{
				printf(" ... \e[32mOK\e[0m\n");
				fprintf(report, "{\\tt %s} \\hfill {\\tt OK} \\\\\n",
				    runner->description);	
			}
			else
			{
				printf(" ... \e[31mFAIL\e[0m '%s' != '%s'\n", runner->expected,
				    runner->actual);

				fprintf(report, "{\\tt %s} \\hfill {\\tt Fail} \n",
				    runner->description);	
				fprintf(report, "\\begin{description}\n");
					fprintf(report, "\\item[Expected] \\hfill \\\\\n");
					fprintf(report, "%s\n", runner->expected);

					fprintf(report, "\\item[Actual] \\hfill \\\\\n");
					fprintf(report, "%s\n", runner->actual);
				fprintf(report, "\\end{description}\n");
			}

			c_idx++;
		}
		
		unit_tests[t_idx].clean(head);
		fprintf(report, "\\newpage");
	}

	fprintf(report, "\\end{document}\n");
	fclose(report);

	return 0;
}

