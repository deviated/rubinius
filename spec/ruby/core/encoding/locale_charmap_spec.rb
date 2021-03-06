require File.expand_path('../../../spec_helper', __FILE__)

with_feature :encoding do
  describe "Encoding.locale_charmap" do
    it "returns a String" do
      Encoding.locale_charmap.should be_an_instance_of(String)
    end

    # FIXME: Get this working on Windows
    platform_is :os => [:darwin, :linux] do
      # FIXME: This spec fails on Mac OS X because it doesn't have ANSI_X3.4-1968 locale.
      # FIXME: If ENV['LC_ALL'] is already set, it comes first.
      it "returns a value based on the LANG environment variable" do
        old_lang = ENV['LANG']
        ENV['LANG'] = 'C'
        ruby_exe("print Encoding.locale_charmap").should == 'ANSI_X3.4-1968'
        ENV['LANG'] = old_lang
      end

      it "is unaffected by assigning to ENV['LANG'] in the same process" do
        old_charmap = Encoding.locale_charmap
        old_lang = ENV['LANG']
        ENV['LANG'] = 'C'
        Encoding.locale_charmap.should == old_charmap
        ENV['LANG'] = old_lang
      end
    end
  end
end
