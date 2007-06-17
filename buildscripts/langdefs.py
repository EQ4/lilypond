#!@PYTHON@
#-*- coding: utf-8 -*-

"""
Documentation i18n module
"""

import re

def lang_file_name (p, langext, ext):
    if langext != '':
        return p + '.' + langext + ext
    return p + ext

class LanguageDef:
    def __init__ (self, code, name, webext=None, double_punct_char_sep='', html_filter=lambda s: s):
        self.code = code
        self.name = name
        self.enabled = True
        if webext == None:
            self.webext = self.code
        else:
            self.webext = webext
        self.double_punct_char_sep = double_punct_char_sep
        self.html_filter = html_filter
    
    def file_name (self, prefix, ext):
        return lang_file_name (prefix, self.webext, ext)


# All language information needed for documentation i18n is defined
# here. For each 'Documentation/ab' directory containing docs
# translated in 'ab', there should be one entry in LANGUAGES.

site = LanguageDef ('en', 'English', webext='')

html_page_body = re.compile ('</?body>', re.M | re.I)
french_html_typo_rules = ((' :', '&nbsp;:'),
                          (' ;', '&nbsp;;'),
                          (' ?', '&thinsp;?'),
                          (' !', '&thinsp;!'))

def french_html_filter (page):
    parts = html_page_body.split (page)
    for r in french_html_typo_rules:
        parts[1] = parts[1].replace (r[0], r[1])
    return parts[0] + '<body>' + parts[1] + '</body>' + parts[2]

fr = LanguageDef ('fr', 'français', double_punct_char_sep='&nbsp;', html_filter = french_html_filter)
es = LanguageDef ('es', 'español')
de = LanguageDef ('de', 'deutsch')

# Outdated or broken translations may be disabled
# (please run 'make web-clean' before doing that):
#fr.enabled = False

LANGUAGES = (site, fr, es, de)

if __name__ == '__main__':
    print ' '.join ([l.code for l in LANGUAGES if l.enabled and l.code != 'en'])
else:
    LANGDICT = {}
    for l in LANGUAGES:
        LANGDICT[l.code] = l
