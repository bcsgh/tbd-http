def env(env, fmt):
    return [_.format(**env) for _ in fmt if _]
