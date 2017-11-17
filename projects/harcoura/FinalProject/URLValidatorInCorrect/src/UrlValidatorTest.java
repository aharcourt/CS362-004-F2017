/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   public void testManualTest()
   {
	   System.out.println("Begining Manual Test: ");
	   
	   String[] testURLs = {
			   ("http://www.facebook.com"), 
			   ("www.facebook.com"), 
			   ("http:/256.256.256.256:-1/..?action=view"), 
			   ("http://125.125.125.125"), 
			   ("http://www.google.com:80/test1?action=view"),
			   ("http://www.aaa.com"),
			   ("http://0.0.0.0:80/test1?action=view"),
			   ("aaa"),
			   ("777"),
			   (""),
			   ("chrome.extension://google.com"),
			   ("http://www.someuniversity.edu:80/path?query_string"),
			   ("http://www.someuniversity:80/path"),
			   ("http://www.someuniversity:80/"),
			   ("http://www.someuniversity:80"),
			   ("httpwww.amazon.com"),
			   ("http://www.amazon"),
			   ("http://www.loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong.com"),
			   ("htp://www.facebook.com\""),
			   ("http://0.0.0.0:0")	   
	   };
	   
	   String[] expectedResults = {
			   ("true"), 
			   ("true"), 
			   ("false"), 
			   ("true"),
			   ("true"),
			   ("true"),
			   ("true"),
			   ("false"),
			   ("false"),
			   ("false"),
			   ("true"),
			   ("true"),
			   ("true"),
			   ("true"),
			   ("true"),
			   ("false"),
			   ("false"),
			   ("false"),
			   ("false"),
			   ("true")
	   };
	   
	   int numOfTests = testURLs.length;
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   for(int i = 0; i < numOfTests; i++){
		   System.out.println("Test URL: " + testURLs[i]);
		   System.out.println("Expected Result: " + expectedResults[i]+ "  Actual Result: " + urlVal.isValid(testURLs[i]));
	   }
	   
	   
	   //System.out.println(urlVal.isValid("http://0.0.0.0:80/test1?action=view"));
	   
	   
   }
   
   
   public void testPartitionScheme() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all schemes that we will be testing
	   ResultPair[] schemes = {
			   new ResultPair("http://", true),
			   new ResultPair("Ftp://", true),
			   new ResultPair("1http://", false),
			   new ResultPair("httP0+-.://", true),
			   new ResultPair("http_$!://", false),
			   new ResultPair("http", false),
			   new ResultPair("", true)
	   };
	   numTests = schemes.length;
	   
	   // Display Testing Header
	   System.out.println("\n>>>>>>>>>>>> Partition Test: URL Scheme <<<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = schemes[i].item + "www.google.com";
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != schemes[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testPartitionAuthority() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all authorities that we will be testing
	   ResultPair[] authorities = {
			   new ResultPair("oregonstate.edu", true),
			   new ResultPair("www.10best.com", true),
			   new ResultPair("www.google.com/webhp", true),
			   new ResultPair("256.255.255.255", false),
			   new ResultPair(".0.0.0.0.", false),
			   new ResultPair("255.255.255.255", true),
			   new ResultPair("0.0.0.0", true),
			   new ResultPair("", false)
	   };
	   numTests = authorities.length;
	   
	   // Display Testing Header
	   
	   System.out.println("\n>>>>>>>>>> Partition Test: URL Authority <<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = "http://" + authorities[i].item;
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != authorities[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testPartitionPort() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all ports that we will be testing
	   ResultPair[] ports = {
			   new ResultPair("", true),
			   new ResultPair(":8080", true),
			   new ResultPair(":0", true),
			   new ResultPair(":65535", true),
			   new ResultPair(":-1.", false),
			   new ResultPair("65536", false),
			   new ResultPair("8080", false),
			   new ResultPair("abcd", false)
	   };
	   numTests = ports.length;
	   
	   // Display Testing Header
	   
	   System.out.println("\n>>>>>>>>>>>>> Partition Test: URL Port <<<<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = "http://www.google.com" + ports[i].item;
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != ports[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testPartitionPath() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all paths that we will be testing
	   ResultPair[] paths = {
			   new ResultPair("", true),
			   new ResultPair("/path/path", true),
			   new ResultPair("Path/path", false),
			   new ResultPair("/path?/path", false),
			   new ResultPair("/path01/&path!", true)
	   };
	   numTests = paths.length;
	   
	   // Display Testing Header
	   
	   System.out.println("\n>>>>>>>>>>>>> Partition Test: URL Path <<<<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = "http://www.google.com" + paths[i].item;
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != paths[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testPartitionQuery() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all queries that we will be testing
	   ResultPair[] queries = {
			   new ResultPair("", true),
			   new ResultPair("?key=value", true),
			   new ResultPair("Key=value", false),
			   new ResultPair("?KeyValue", false),
			   new ResultPair("?key=value&key2=value2", true)
	   };
	   numTests = queries.length;
	   
	   // Display Testing Header
	   
	   System.out.println("\n>>>>>>>>>>>>>> Partition Test: URL Query <<<<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = "http://www.google.com" + queries[i].item;
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != queries[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testIsValid()
   {
	   for(int i = 0; i <10000; i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
