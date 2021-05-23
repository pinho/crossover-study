'''Boxplot Styles

Defines stylization functions to apply in boxplot dictionaries
'''

# Boxplot dictionary keys:
BP_KEYS = ['boxes', 'medians', 'whiskers', 'caps', 'fliers', 'means']

# Pre-defined Props
green_diamond = dict(marker='D', markeredgecolor='white', makerfacecolor='green', markersize=2)
red_diamond = dict(marker='D', markeredgecolor='white', makerfacecolor='red', markersize=2)
yellow_diamond = dict(marker='D', markeredgecolor='white', makerfacecolor='yellow', markersize=2)

black_box = dict(linestyle='-', color='white', facecolor='black')

def black_boxes(bp: dict):
    marker_size = 7.5
    marker_style = 'D'

    for box in bp['boxes']:
        box.set_color('#ccc')
        box.set_facecolor('black')
    
    for median in bp['medians']:
        median.set_color('#ccc')
        median.set_linewidth(2)
    
    for cap in bp['caps']:
        cap.set_color('black')
        cap.set_linewidth(2)

    for whisker in bp['whiskers']:
        whisker.set_color('black')
        whisker.set_linewidth(2)

    for flier in bp['fliers']:
        flier.set_markerfacecolor('#dc2f02')
        flier.set_markeredgecolor('orange')
        flier.set_markersize(marker_size)
        flier.set_marker(marker_style)

    for mean in bp['means']:
        mean.set_markerfacecolor('#38b000')
        mean.set_markeredgecolor('#7ae582')
        mean.set_markeredgewidth(2.5)
        mean.set_markersize(marker_size)
        mean.set_marker(marker_style)
