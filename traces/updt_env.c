
char **actualize_env(t_env *env, char **str_env) {
	t_env *current = env;
	size_t len_key, len_value;
	int index = 0;

	str_env = (char **)malloc(sizeof(char *) * (count_env(current) + 1));
	if (!str_env)
		return (NULL);
	while (current) {
		len_key = strlen(current->key);
		len_value = strlen(current->value);

		str_env[index] = (char *)malloc(len_key + len_value + 2);
		if (!str_env[index]) {
			while (index >= 0) {
				free(str_env[index]);
				index--;
			}
			free(str_env);
			return NULL;
		}
		ft_strjoin(str_env[index], current->key);
		ft_charjoin(str_env[index], '=');
		strcpy(&str_env[index][len_key + 1], current->value);

		index++;
		current = current->next;
	}
	str_env[index] = NULL;
	return (str_env);
}