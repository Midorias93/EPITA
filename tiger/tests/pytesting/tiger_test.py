import io
import subprocess

def scan_errors(testname):
    ref = open('ref_'+testname+'.txt', 'r')
    reflines = ref.readlines()
    ref.close()
    args = ["../../src/tc", "test_"+testname+".tig"]
    popen = subprocess.Popen(args, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    popen.wait()
    testlines = popen.stderr.readlines()
    '''
    for refline, testline in zip(reflines, io.TextIOWrapper(popen.stderr, encoding="utf-8")):
        assert(refline)
        assert(testline)
        assert(refline == testline)
    '''
    print(testlines)
    assert(reflines == testlines)
def test_run():
    scan_errors("scan_errors")
test_run()
