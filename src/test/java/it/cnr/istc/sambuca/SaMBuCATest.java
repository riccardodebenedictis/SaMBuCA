package it.cnr.istc.sambuca;

import java.io.IOException;

import org.junit.jupiter.api.Test;

/**
 * SaMBuCATest
 */
public class SaMBuCATest {

    @Test
    public void testBlocks() {
        try {
            SaMBuCA smb = new SaMBuCA(SaMBuCATest.class.getResource("blocks-domain.pddl").getPath(),
                    SaMBuCATest.class.getResource("blocks-problem.pddl").getPath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}