function checker()
	total_points = 0;
	input_files = ['image1'; 'image2'; 'image3'; 'image4'];
	no_tests = 4;
	epsilon = 10^-3;
  
	printf('----------------------------------------------------------------------------\n');
	printf('----------------------------------------------------------------------------\n');
	printf('---------------------------- Testare Tema 2 MN -----------------------------\n');
	printf('----------------------------------------------------------------------------\n');
	printf('----------------------------------------------------------------------------\n');
	
  mkdir('out/');
 
 	k = [2 25];
	
  for i = 1 : no_tests
	
		printf('----------------Imagine %d \n', i);
		
		%%% executie tema pentru un fisier de intrare
		name = input_files(i, 1:6);
		Tema2MN(name, k);

    %%% ------------------------------------------------------------------------------------------------------------
		%%% Testare Cerinta 1
		%%% ------------------------------------------------------------------------------------------------------------
    if (fid_aux = fopen('cerinta1.m', 'r')) ~= -1
			fclose(fid_aux);
			
      for i = 1 : length(k)
			  image_ref = strcat('ref/cerinta1_', strcat(name, strcat('_', strcat(num2str(k(i)),'.gif'))));
        image_out = strcat('out/cerinta1_', strcat(name, strcat('_', strcat(num2str(k(i)),'.gif'))));
    
        image_ref_matrix = double(imread(image_ref));
        image_out_matrix = double(imread(image_out));

        success = 1;
        [m, n] = size(image_ref_matrix);
        for l = 1 : m
          for j = 1 : n 
            if abs(image_ref_matrix(l,j) - image_out_matrix(l,j)) > epsilon
              success = 0;
              break;
            end
          end
          if success == 0
            break;
          end
        end
			   
			  if success == 0 
				  printf('Cerinta 1, k = %d ................................................. Incorect [%d/%d]\n', k(i), 0, 1.875);
			  else
				  total_points += 1.875;
				  printf('Cerinta 1, k = %d .......................................... Corect [%d/%d]\n', k(i), 1.875, 1.875);
			  endif
       end 
		else
			printf('Cerinta 1 nu a fost implementata \n');
		endif

    %%% ------------------------------------------------------------------------------------------------------------
		%%% Testare Cerinta 3
		%%% ------------------------------------------------------------------------------------------------------------
    if (fid_aux = fopen('cerinta3.m', 'r')) ~= -1
			fclose(fid_aux);
			
      for i = 1 : length(k)
			  image_ref = strcat('ref/cerinta3_', strcat(name, strcat('_', strcat(num2str(k(i)),'.gif'))));
        image_out = strcat('out/cerinta3_', strcat(name, strcat('_', strcat(num2str(k(i)),'.gif'))));
    
        image_ref_matrix = double(imread(image_ref));
        image_out_matrix = double(imread(image_out));

        success = 1;
        [m, n] = size(image_ref_matrix);
        for l = 1 : m
          for j = 1 : n 
            if abs(image_ref_matrix(l,j) - image_out_matrix(l,j)) > epsilon
              success = 0;
              break;
            end
          end
          if success == 0
            break;
          end
        end
			   
			  if success == 0 
				  printf('Cerinta 3, k = %d ................................................. Incorect [%d/%d]\n', k(i), 0, 3.125);
			  else
				  total_points += 3.125;
				  printf('Cerinta 3, k = %d .......................................... Corect [%d/%d]\n', k(i), 3.125, 3.125);
			  endif
       end 
		else
			printf('Cerinta 3 nu a fost implementata \n');
		endif
	
    %%% ------------------------------------------------------------------------------------------------------------
		%%% Testare Cerinta 4
		%%% ------------------------------------------------------------------------------------------------------------
    if (fid_aux = fopen('cerinta4.m', 'r')) ~= -1
			fclose(fid_aux);
			
      for i = 1 : length(k)
			  image_ref = strcat('ref/cerinta4_', strcat(name, strcat('_', strcat(num2str(k(i)),'.gif'))));
        image_out = strcat('out/cerinta4_', strcat(name, strcat('_', strcat(num2str(k(i)),'.gif'))));
    
        image_ref_matrix = double(imread(image_ref));
        image_out_matrix = double(imread(image_out));

        success = 1;
        [m, n] = size(image_ref_matrix);
        for l = 1 : m
          for j = 1 : n 
            if abs(image_ref_matrix(l,j) - image_out_matrix(l,j)) > epsilon
              success = 0;
              break;
            end
          end
          if success == 0
            break;
          end
        end
			   
			  if success == 0 
				  printf('Cerinta 4, k = %d ................................................. Incorect [%d/%d]\n', k(i), 0, 1.875);
			  else
				  total_points += 1.875;
				  printf('Cerinta 4, k = %d .......................................... Corect [%d/%d]\n', k(i), 1.875, 1.875);
			  endif
       end 
		else
			printf('Cerinta 4 nu a fost implementata \n');
		endif
	endfor  
  
	printf('\n                                      Punctaj total tema: [%d/%d]\n\n', total_points, 55);
endfunction