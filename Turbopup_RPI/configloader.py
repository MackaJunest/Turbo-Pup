import configparser

# Read the configuration file
config = configparser.ConfigParser()
config.read('config.ini')

# Extract the values from the config file
max_speed = config.getint('Settings', 'max_speed')
turning_scale_factor = config.getfloat('Settings', 'turning_scale_factor')

