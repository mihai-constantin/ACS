function check()

no_tests=2;
grades=zeros(1,no_tests);

EPSILON=0.001;

printf('=== Checker homework 1 ===\n')

for i =1:no_tests

	%% Run homework on a given input file
	test_intrare=strcat('graf', num2str(i));
	printf('\n--- Run test %d on file \"%s\"\n', i, test_intrare);
	unlink(strcat(test_intrare, '.out'));
	PageRank(test_intrare, 0.85, EPSILON);

	%% open both output and ref files
	fid_out = fopen(strcat(test_intrare, '.out'), 'r');
	fid_ref = fopen(strcat(test_intrare, '.ref'), 'r');

	%% read all output and ref contents
	out = fscanf(fid_out, "%lf");
	ref = fscanf(fid_ref, "%lf");

	%% close files
	fclose(fid_out);
	fclose(fid_ref);

	n_out = uint8(out(1));
	n_ref = uint8(ref(1));

	if n_out ~= n_ref
		%% graph with different sizes
		grades(i) = grades(i) + 0;
		printf('    %-12s %3d p (output: %d, expected: %d)\n',
				'Length', 0, n_out, n_ref);
	else

		%% test first part (Iterative - 40p)
		test_1=0;
		for x=1:n_out
			if abs(out(1 + x) - ref(1 + x)) > EPSILON
				test_1=x;
				break;
			endif
		endfor

		if test_1 == 0
			grades(i) = grades(i) + 40;
			printf('    %-12s %3d p\n', 'Iterative', 40);
		else
			grades(i) = grades(i) + 0;
			printf('    %-12s %3d p (difference at index %d)\n', 'Iterative', 0, test_1);
		endif

		%% test second part (Algebraic - 40p)
		test_2=0;
		for x=1:n_out
			if abs(out(1 + x + n_out) - ref(1 + x + n_out)) > EPSILON
				test_2=x;
				break;
			endif
		endfor

		if test_2 == 0
			grades(i) = grades(i) + 40;
			printf('    %-12s %3d p\n', 'Algebraic', 40);
		else
			grades(i) = grades(i) + 0;
			printf('    %-12s %3d p (value difference at index %d)\n',
					'Algebraic', 0, test_2);
		endif

		%% test final part
		test_final=0;
		for x=1:3:n_out * 3
			i1_out = int32(out(1 + 2 * n_out + x));
			i2_out = int32(out(1 + 2 * n_out + x + 1));
			i3_out = out(1 + 2 * n_out + x + 2);

			i1_ref = int32(ref(1 + 2 * n_ref + x));
			i2_ref = int32(ref(1 + 2 * n_ref + x + 1));
			i3_ref = ref(1 + 2 * n_ref + x + 2);

			if i1_out ~= i1_ref || i2_out ~= i2_ref || abs(i3_out - i3_ref) > EPSILON
				test_final=x;
				break;
			endif
		endfor

		if test_final == 0
			grades(i) = grades(i) + 20;
			printf('    %-12s %3d p\n', 'Apartenenta', 20);
		else
			grades(i) = grades(i) + 0;
			printf('    %-12s %3d p (value difference at index %d)\n', 'Apartenenta', 0, test_final);
		endif
	endif
	printf('\n    %-12s %3d p\n', 'Final', grades(i));
endfor

printf('\n=== Homework score: %d p ===\n', sum(grades) / no_tests);
