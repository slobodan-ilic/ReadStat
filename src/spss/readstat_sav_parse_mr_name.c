
#line 1 "./src/spss/readstat_sav_parse_mr_name.rl"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../readstat.h"
#include "../readstat_malloc.h"
#include "readstat_sav_parse_mr_name.h"


#line 12 "./src/spss/readstat_sav_parse_mr_name.c"
static const char _parse_multiple_response_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4
};

static const char _parse_multiple_response_key_offsets[] = {
	0, 0, 7, 15, 17, 20, 22, 25, 
	33, 44
};

static const char _parse_multiple_response_trans_keys[] = {
	95, 48, 57, 65, 90, 97, 122, 61, 
	95, 48, 57, 65, 90, 97, 122, 67, 
	68, 32, 48, 57, 48, 57, 32, 48, 
	57, 32, 95, 48, 57, 65, 90, 97, 
	122, 0, 32, 95, 9, 13, 48, 57, 
	65, 90, 97, 122, 95, 48, 57, 65, 
	90, 97, 122, 0
};

static const char _parse_multiple_response_single_lengths[] = {
	0, 1, 2, 0, 1, 0, 1, 2, 
	3, 1
};

static const char _parse_multiple_response_range_lengths[] = {
	0, 3, 3, 1, 1, 1, 1, 3, 
	4, 3
};

static const char _parse_multiple_response_index_offsets[] = {
	0, 0, 5, 11, 13, 16, 18, 21, 
	27, 35
};

static const char _parse_multiple_response_indicies[] = {
	0, 0, 0, 0, 1, 2, 0, 0, 
	0, 0, 1, 3, 1, 4, 5, 1, 
	6, 1, 7, 6, 1, 8, 9, 9, 
	9, 9, 1, 10, 10, 9, 10, 9, 
	9, 9, 1, 9, 9, 9, 9, 1, 
	0
};

static const char _parse_multiple_response_trans_targs[] = {
	2, 0, 3, 4, 5, 4, 6, 7, 
	7, 8, 9
};

static const char _parse_multiple_response_trans_actions[] = {
	0, 0, 1, 3, 5, 0, 0, 7, 
	0, 0, 9
};

static const int parse_multiple_response_start = 1;

static const int parse_multiple_response_en_main = 1;


#line 11 "./src/spss/readstat_sav_parse_mr_name.rl"



readstat_error_t extract_mr_data(const char *line, mr_set_t *result) {
    readstat_error_t retval = READSTAT_OK;

    // Variables needed for Ragel operation
    int cs = 0;
    char *p = (char *)line;
    char *start = p;
    char *pe = p + strlen(p) + 1;

    // Variables needed for passing Ragel intermediate results
    char mr_type = '\0';
    int mr_counted_value = -1;
    int mr_subvar_count = -1;
    char** mr_subvariables = NULL;
    char* mr_name = NULL;
    char* mr_label = NULL;

    // Execute Ragel finite state machine (FSM)
    
#line 95 "./src/spss/readstat_sav_parse_mr_name.c"
	{
	cs = parse_multiple_response_start;
	}

#line 100 "./src/spss/readstat_sav_parse_mr_name.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _parse_multiple_response_trans_keys + _parse_multiple_response_key_offsets[cs];
	_trans = _parse_multiple_response_index_offsets[cs];

	_klen = _parse_multiple_response_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _parse_multiple_response_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _parse_multiple_response_indicies[_trans];
	cs = _parse_multiple_response_trans_targs[_trans];

	if ( _parse_multiple_response_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _parse_multiple_response_actions + _parse_multiple_response_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 33 "./src/spss/readstat_sav_parse_mr_name.rl"
	{
            mr_name = readstat_malloc(p - start + 1);
            memcpy(mr_name, start, p - start);
            mr_name[p - start] = '\0';
        }
	break;
	case 1:
#line 39 "./src/spss/readstat_sav_parse_mr_name.rl"
	{
            mr_type = *p;
            start = p + 1;
        }
	break;
	case 2:
#line 44 "./src/spss/readstat_sav_parse_mr_name.rl"
	{
            int n_cv_digs = p - start;
            char *n_dig_str = readstat_malloc(n_cv_digs + 1);
            memcpy(n_dig_str, start, n_cv_digs);
            n_dig_str[n_cv_digs] = '\0';
            int n_digs = strtol(n_dig_str, NULL, 10);
            if (n_digs != 0) {
                char *cv = readstat_malloc(n_digs + 1);
                memcpy(cv, p + 1, n_digs);
                cv[n_digs] = '\0';
                mr_counted_value = strtol(cv, NULL, 10);
                p = p + 1 + n_digs;
                start = p + 1;
            }
            else {
                mr_counted_value = -1;
            }
        }
	break;
	case 3:
#line 63 "./src/spss/readstat_sav_parse_mr_name.rl"
	{
            char *lbl_len_str = readstat_malloc(p - start + 1);
            memcpy(lbl_len_str, start, p - start);
            lbl_len_str[p - start] = '\0';
            int len = strtol(lbl_len_str, NULL, 10);
            mr_label = readstat_malloc(len + 1);
            memcpy(mr_label, p + 1, len);
            mr_label[len] = '\0';
            p = p + 1 + len;
            start = p + 1;
        }
	break;
	case 4:
#line 75 "./src/spss/readstat_sav_parse_mr_name.rl"
	{
            int len = p - start;
            char *subvar = readstat_malloc(len + 1);
            memcpy(subvar, start, len);
            subvar[len] = '\0';
            start = p + 1;

            mr_subvariables = readstat_realloc(mr_subvariables, sizeof(char *) * (mr_subvar_count + 1));
            mr_subvariables[mr_subvar_count++] = subvar;
        }
	break;
#line 237 "./src/spss/readstat_sav_parse_mr_name.c"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 99 "./src/spss/readstat_sav_parse_mr_name.rl"


    if (cs < 9 || p != pe) {
        retval = READSTAT_ERROR_BAD_MR_STRING;
        goto cleanup;
    }

    // Assign parsed values to output parameter
    result->name = mr_name;
    result->label = mr_label;
    result->type = mr_type;
    result->counted_value = mr_counted_value;
    result->subvariables = mr_subvariables;
    result->num_subvars = mr_subvar_count;
    if (result->type == 'D') {
        result->is_dichotomy = 1;
    }

cleanup:
    if (retval != READSTAT_OK) {
        if (mr_subvariables != NULL) {
            for (int i = 0; i < mr_subvar_count; i++) {
                if (mr_subvariables[i] != NULL) free(mr_subvariables[i]);
            }
            free(mr_subvariables);
        }
        if (mr_name != NULL) free(mr_name);
        if (mr_label != NULL) free(mr_label);
    }

    (void)parse_multiple_response_en_main;

    return retval;
}


readstat_error_t parse_mr_line(const char *line, mr_set_t *result) {
    readstat_error_t retval = READSTAT_OK;
    *result = (mr_set_t){0};

    retval = extract_mr_data(line, result);
    return retval;
}
